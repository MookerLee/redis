

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
		typedef std::list<std::string> stringList;

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


		std::string serializeSimpleCommand(const std::string& simpleCmd)
		{
			stringList commands;
			splitSimpleCommand(commands, simpleCmd, " ");
			return serialize(commands);
		}

		template<class... Args>
		std::string serializeSafeCommand(Args... args)
		{
			stringList commands;
			analysisArgs(commands,std::forward<Args>(args)...);
			return serialize(commands);

		}

		template<class ValueType, class... Args>
		static void analysisArgs(stringList& commands, ValueType arg, Args... args)
		{
			commands.push_back(stringConvert::toString(arg));
			analysisArgs(commands,args...);
		}
		static void analysisArgs(stringList&) {}


		template<class... Args>
		std::string serializePairsCommand(const std::string& cmd, std::initializer_list<Args>... pairs)
		{
			stringList commands;
			commands.push_back(cmd);
			analysisPairs(commands, pairs...);
			return serialize(commands);
		}

		template <class ValueType, class... Args>
		static void analysisPairs(stringList& commands, ValueType pair, std::initializer_list<Args>... pairs)
		{

			for (auto it = pair.begin(); it != pair.end(); ++it)
				commands.push_back(stringConvert::toString(*it));
			
			analysisPairs(commands, pairs...);
		}
		static void analysisPairs(stringList&) {}


		template<class... Args>
		std::string serializePairsCommand(const std::string& cmd,const std::string& key,  std::initializer_list<Args>... pairs)
		{
			stringList commands;

			commands.push_back(cmd);
			commands.push_back(key);

			analysisPairs(commands, pairs...);
			return serialize(commands);
		}
		/**
		* 保存并检测整条数据是否接收完毕
		*/
		void feedBuffer(const std::string& readString)
		{
			buffer_.append(readString.c_str(), readString.length());
		}

		void clearBuffer()
		{
			buffer_.clear();
		}
		std::shared_ptr<replyImpl> biludReplyImpl()
		{
			
			// 如果最后不是\r\n 一定没有读完
			if (buffer_.find_last_of("\r\n") == std::string::npos) return nullptr;

			stringList commands;
			splitSimpleCommand(commands, buffer_, "\r\n");

			if (commands.front()[0] == '$' && commands.front().substr(1) == "-1")
				throw exception(exception::errorCode::REPLY_VAL_NONEXIST, "reply val non-exist");

			std::shared_ptr<replyImpl> impl;

			if ((impl = buildSingleReply(commands))) return impl;
			if ((impl = buildStringReply(commands))) return impl;
			if ((impl = buildArrayReply(commands))) return impl;
			

			return nullptr;
		}


		static protocol::replyType analysisReplyType(const std::string& buffer)
		{
			if (buffer.empty()) return protocol::replyType::REPLY_UNKNOW;

			switch (buffer[0])
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
		
		std::shared_ptr<replyImpl> buildSingleReply(const stringList& commands)
		{
			/************************************************************************/
			/*   ":0\r\n" 和 ":1000\r\n"												*/
			/************************************************************************/

			if (commands.size() != 1) return nullptr;

			protocol::replyType type = analysisReplyType(commands.front());
			switch (type)
			{
			case protocol::REPLY_STATUS:
			case protocol::REPLY_ERROR:
			case protocol::REPLY_INTEGER:
			{
				std::string val = commands.front().substr(1);
				return std::make_shared<replyImpl>(transformReplyType(type), val);
			}
		
			default:
				break;
			}
			return nullptr;
		}

		std::shared_ptr<replyImpl> buildStringReply(const stringList& commands)
		{
			/************************************************************************/
			/*   "$6\r\nfoobar\r\n"													*/
			/************************************************************************/

			if (commands.size() != 2) return nullptr;
			protocol::replyType type = analysisReplyType(commands.front());
			if (type != protocol::replyType::REPLY_BULK) return nullptr;

			long long len = std::stoll(commands.front().substr(1));
			if (len != commands.back().size()) return nullptr;

			return std::make_shared<replyImpl>(transformReplyType(type), commands.back());
		}

		std::shared_ptr<replyImpl> buildArrayReply(const stringList& commands)
		{
			/************************************************************************/
			/*  *5\r\n
			:1\r\n
			:2\r\n
			:3\r\n
			:4\r\n
			$6\r\n
			foobar\r\n                                                          */
			/************************************************************************/

			protocol::replyType type = analysisReplyType(commands.front());
			if (type != protocol::replyType::REPLY_MULTI_BULK) return nullptr;

			size_t arraySzie = std::stoll(commands.front().substr(1));
			size_t buildCount = 0;

			std::shared_ptr<replyImpl> replyArray(std::make_shared<replyImpl>(transformReplyType(type), ""));
			
			for (auto it = std::next(commands.begin()); it != commands.end(); ++it)
			{
				std::shared_ptr<replyImpl> replySub;

				if ((replySub = buildSingleReply({ *it })))
				{
					replyArray->pushImpl(replySub);
					buildCount++;
				}
				else if ((replySub = buildStringReply({ *it,*std::next(it) })))
				{
					replyArray->pushImpl(replySub);
					buildCount++;

					it = std::next(it);
				}
				else if ((replySub = buildArrayReply(stringList(it, commands.end()))))
				{
					replyArray->pushImpl(replySub);
					buildCount++;

					break;
				}
				else return nullptr;			
			}

			if (buildCount == arraySzie) return replyArray;

			return nullptr;
		}


		replyImpl::replyType transformReplyType(protocol::replyType type)
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

		std::string serialize(const stringList& commands)
		{
			/************************************************************************/
			/*      *<参数数量> CR LF                                                */
			/*		$<参数 1 的字节数量> CR LF										*/
			/*		...																*/
			/*		$<参数 N 的字节数量> CR LF										*/
			/*		<参数 N 的数据> CR LF												*/
			/************************************************************************/
			std::string serializeStr;

			serializeStr.append("*");
			serializeStr.append(std::to_string(commands.size()));
			serializeStr.append("\r\n");

			for (const auto& command : commands)
			{
				serializeStr.append("$");
				serializeStr.append(std::to_string(command.size()));
				serializeStr.append("\r\n");
				serializeStr.append(command.c_str(), command.size());
				serializeStr.append("\r\n");
			}

			return serializeStr;
		}

		static void splitSimpleCommand(stringList& commands, const std::string& simpleCmd, const std::string& split)
		{
			if (simpleCmd.empty()) return;

			if (simpleCmd[0] == ' ') return splitSimpleCommand(commands, simpleCmd.substr(1), split);

			size_t pos = std::string::npos;

			std::string _spit = split;
			if (simpleCmd[0] == '\"') _spit = '\"';

			if ((pos = simpleCmd.find_first_of(_spit, 1)) == std::string::npos)
			{
				commands.push_back(simpleCmd);
				return;
			}

			commands.push_back(simpleCmd.substr(0, pos));

			return splitSimpleCommand(commands, simpleCmd.substr(pos + _spit.size()), split);
		}
	private:

		std::string buffer_;
	};
};

#endif