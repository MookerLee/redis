

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

		void feedBuffer(const std::string& buf)
		{
			buffer_.append(buf.c_str(), buf.length());
		}

		void clearBuffer()
		{
			currentPos_ = 0;
			buffer_.clear();
		}

		std::string currentPosString()
		{
			size_t findPos = buffer_.find_first_of(spiltString_, currentPos_);
			if (findPos == std::string::npos) return "";
			return buffer_.substr(currentPos_, findPos - currentPos_);
		}
		std::shared_ptr<replyImpl> buildStringReply()
		{			
			std::string curStr = currentPosString();

			protocol::replyType type = getReplyType(curStr);
			if (type != protocol::replyType::REPLY_BULK) return nullptr;

			long long dataSize = std::stoll(curStr.substr(1));
			currentPos_ += curStr.length() + spiltString_.length();

			if (dataSize == -1)
			{
				throw exception(exception::errorCode::REPLY_VAL_NONEXIST, "reply val non-exist");
			}

			long long leftBufferSize = buffer_.length() - currentPos_;

			if (leftBufferSize < dataSize + spiltString_.size())
			{
				currentPos_ = 0;
				return nullptr;
			}

			std::shared_ptr<replyImpl> impl(
				std::make_shared<replyImpl>(
					transformReplyType(type), buffer_.substr(currentPos_, dataSize)));

			currentPos_ += dataSize + spiltString_.size();
		
			return impl;
		}
		std::shared_ptr<replyImpl> buildSingleReply()
		{
			std::string curStr = currentPosString();
			protocol::replyType type = getReplyType(curStr);

			switch (type)
			{
			case redis::protocol::REPLY_STATUS:
			case redis::protocol::REPLY_ERROR:
			case redis::protocol::REPLY_INTEGER:
			{
				currentPos_ += curStr.length() + spiltString_.length();
				return std::make_shared<replyImpl>(transformReplyType(type), curStr.substr(1));
			}
				break;
			default:
				return nullptr;
			}
		}

		std::shared_ptr<replyImpl> buildArrayReply()
		{
			std::string curStr = currentPosString();
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
			currentPos_ += curStr.length() + spiltString_.length();

			std::shared_ptr<replyImpl> retImpl(std::make_shared<replyImpl>(transformReplyType(type), ""));

			for (int i = 0; i < arraySize; ++i)
			{
				std::shared_ptr<replyImpl> subImpl;
				subImpl = buildSingleReply();
				if (subImpl)
				{
					retImpl->pushImpl(subImpl);
					continue;
				}
				subImpl = buildStringReply();
				if (subImpl)
				{
					retImpl->pushImpl(subImpl);
					continue;
				}
				subImpl = buildArrayReply();
				if (subImpl)
				{
					retImpl->pushImpl(subImpl);
					continue;
				}
			}
			if (retImpl->asArray().size() != arraySize) return nullptr;
			return retImpl;
		}

		std::shared_ptr<replyImpl> biludReplyImpl()
		{	
			currentPos_ = 0;
			// 如果最后不是\r\n 一定没有读完
			if (buffer_.find_last_of(spiltString_) == std::string::npos) return nullptr;

			std::shared_ptr<replyImpl> retImpl;

			retImpl = buildStringReply();
			if (retImpl) return retImpl;

			retImpl = buildSingleReply();
			if (retImpl) return retImpl;

			retImpl = buildArrayReply();
			if (retImpl) return retImpl;

			return nullptr;
		}


		protocol::replyType getReplyType(const std::string& buf)
		{
			if (buf.empty()) return protocol::replyType::REPLY_UNKNOW;

			switch (buf[0])
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

	private:
		

		static replyImpl::replyType transformReplyType(protocol::replyType type)
		{
			switch (type)
			{

			case protocol::REPLY_UNKNOW: return replyImpl::REPLY_UNKNOW;
			case protocol::REPLY_STATUS: return replyImpl::REPLY_STATUS;
			case protocol::REPLY_ERROR:return replyImpl::REPLY_ERROR;
			case protocol::REPLY_INTEGER:return replyImpl::REPLY_INTEGER;
			case protocol::REPLY_BULK:return replyImpl::REPLY_BULK;
			case protocol::REPLY_MULTI_BULK:return replyImpl::REPLY_MULTI_BULK;

			default:
				return replyImpl::REPLY_UNKNOW;
			}
		}
		
	private:

		std::string buffer_;
		size_t currentPos_ = 0;
		const std::string spiltString_ = "\r\n";
	};
};
#include <redis/impl/protocol_sender.hpp>
#endif