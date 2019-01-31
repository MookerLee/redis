

#ifndef _CXXREDIS_PROTOCOL_IMPL_HPP_
#define _CXXREDIS_PROTOCOL_IMPL_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <string>
#include <list>
#include <algorithm>
#include <cassert>
#include <memory>

#include "redis/impl/reply_impl.hpp"
#include "redis/impl/string_convert.hpp"

#define SPILTSTRING std::string("\r\n")

namespace redis {

	class replyImpl;

	class protocol {

	public:

		class sender;
		enum replyType
		{
			REPLY_UNKNOW,		//未知类型
			REPLY_STATUS,		//状态回复（status reply）的第一个字节是 "+"
			REPLY_ERROR,		//错误回复（error reply）的第一个字节是 "-"
			REPLY_INTEGER,		//整数回复（integer reply）的第一个字节是 ":"
			REPLY_BULK,			//批量回复（bulk reply）的第一个字节是 "$"
			REPLY_MULTI_BULK,	//多条批量回复（multi bulk reply）的第一个字节是 "*"
		};

	public:

		static std::string findFirstSpiltString(const std::string& buffer, size_t offset)
		{
			size_t pos = buffer.find_first_of(SPILTSTRING, offset);
			if (pos == std::string::npos) return "";
			return buffer.substr(offset, pos - offset);
		}
		static std::shared_ptr<replyImpl> buildStringReply(const std::string& buffer,size_t& offset)
		{			
			std::string curStr = findFirstSpiltString(buffer,offset);

			protocol::replyType type = getReplyType(curStr);
			if (type != protocol::replyType::REPLY_BULK) return nullptr;

			long long dataSize = std::stoll(curStr.substr(1));
			offset += curStr.length() + SPILTSTRING.length();

			if (dataSize == -1)
			{
				return std::make_shared<replyImpl>();
			}

			//数据不够或者过长
			if ((buffer.length() - offset) != (dataSize + SPILTSTRING.length())) return nullptr;
			
			std::shared_ptr<replyImpl> impl(
				std::make_shared<replyImpl>(
					replyImpl::replyType::REPLY_BULK, buffer.substr(offset, dataSize)));
			offset += dataSize + SPILTSTRING.length();
		
			return impl;
		}
		static std::shared_ptr<replyImpl> buildSingleReply(const std::string& buffer,size_t& offset)
		{
			std::string curStr = findFirstSpiltString(buffer, offset);
			protocol::replyType type = getReplyType(curStr);

			switch (type)
			{
			case redis::protocol::REPLY_STATUS:
			case redis::protocol::REPLY_ERROR:
			case redis::protocol::REPLY_INTEGER:
			{
				offset += curStr.length() + SPILTSTRING.length();

				replyImpl::replyType replytype;
				if (type == redis::protocol::REPLY_STATUS) replytype = replyImpl::replyType::REPLY_STATUS;
				else if (type == redis::protocol::REPLY_ERROR) replytype = replyImpl::replyType::REPLY_ERROR;
				else if (type == redis::protocol::REPLY_INTEGER) replytype = replyImpl::replyType::REPLY_INTEGER;

				return std::make_shared<replyImpl>(replytype, curStr.substr(1));
			}
				break;
			default:
				return nullptr;
			}
		}

		static std::shared_ptr<replyImpl> buildArrayReply(const std::string& buffer, size_t& offset)
		{
			std::string curStr = findFirstSpiltString(buffer,offset);
			protocol::replyType type = getReplyType(curStr);

			if (type != protocol::replyType::REPLY_MULTI_BULK) return nullptr;

			/************************************************************************/
			/*  *5\r\n
			:1\r\n
			:2\r\n
			:3\r\n
			:4\r\n
			$6\r\n
			foobar\r\n                                                          */
			/************************************************************************/

			long long arraySize = std::stoll(curStr.substr(1));
			offset += curStr.length() + SPILTSTRING.length();

			std::vector<std::shared_ptr<replyImpl>> impls;

			for (int i = 0; i < arraySize; ++i)
			{
				std::shared_ptr<replyImpl> impl;
				impl = buildSingleReply(buffer, offset);
				if (impl)
				{
					impls.push_back(impl);
					continue;
				}
				impl = buildStringReply(buffer, offset);
				if (impl)
				{
					impls.push_back(impl);
					continue;
				}
				impl = buildArrayReply(buffer,offset);
				if (impl)
				{
					impls.push_back(impl);
					continue;
				}
			}
			std::shared_ptr<replyImpl> retImpl(std::make_shared<replyImpl>(impls));
			if (retImpl->array().size() != arraySize) return nullptr;
			return retImpl;
		}

		static std::shared_ptr<replyImpl> biludReplyImpl(const std::string& buffer)
		{	
			// 如果最后不是\r\n 一定没有读完
			if (buffer.find_last_of(SPILTSTRING) == std::string::npos) return nullptr;

			size_t offset = 0;
			std::shared_ptr<replyImpl> retImpl;

			retImpl = buildStringReply(buffer, offset);
			if (retImpl) return retImpl;

			retImpl = buildSingleReply(buffer, offset);
			if (retImpl) return retImpl;

			retImpl = buildArrayReply(buffer, offset);
			if (retImpl) return retImpl;

			return nullptr;
		}


		static protocol::replyType getReplyType(const std::string& str)
		{
			if (str.empty()) return protocol::replyType::REPLY_UNKNOW;

			switch (str[0])
			{
			case '+': return protocol::replyType::REPLY_STATUS;
			case '-': return protocol::replyType::REPLY_ERROR;
			case ':': return protocol::replyType::REPLY_INTEGER;
			case '$': return protocol::replyType::REPLY_BULK;
			case '*': return protocol::replyType::REPLY_MULTI_BULK;
			default:
				break;
			}

			throw exception(exception::errorCode::PROTOCOL_ERROR, "protocol deserialize fail !");
		}
	};
};
#include <redis/impl/protocol_sender.hpp>
#endif