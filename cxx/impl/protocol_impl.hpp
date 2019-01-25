

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

#include "reply_impl.hpp"
#include "redis/cxx/protocol.hpp"

namespace CXXRedis {

	class protocolImpl {

	public:
		typedef std::list<std::string> stringList;

	public:
		protocolImpl(){}
		~protocolImpl(){}

	public:
		std::string serializeSimpleCommand(const std::string& simpleCmd)
		{

			stringList commands;
			splitSimpleCommand(commands, simpleCmd, " ");
			return serialize(commands);
		}

		/**
		* 保存并检测整条数据是否接收完毕
		*/
		std::shared_ptr<replyImpl> feedBuffer(const std::string& readString)
		{
			deserializeBuffer_.append(readString.c_str(), readString.length());
			if (deserializeBuffer_.empty()) return false;
			return deserialize();
		}
		std::shared_ptr<replyImpl> deserialize()
		{
			protocol::replyType type = analysisReplyType(deserializeBuffer_);

			if (type == protocol::replyType::REPLY_UNKNOW) 
				throw exception(
					exception::errorCode::PROTOCOL_ERROR, 
					"protocol deserialize fail !");

			// 如果最后不是\r\n 一定没有读完
			if (deserializeBuffer_.find_last_of("\r\n") == std::string::npos) return nullptr;

			stringList commands;
			splitSimpleCommand(commands, deserializeBuffer_, "\r\n");

			switch (type)
			{
				/************************************************************************/
				/*   ":0\r\n" 和 ":1000\r\n"												*/
				/************************************************************************/

			case protocol::replyType::REPLY_STATUS:
			case protocol::replyType::REPLY_ERROR:
			case protocol::replyType::REPLY_INTEGER:
			{
				return std::make_shared<replyImpl>(type, commands.front().substr(1)) ;
			}
			break;

			/************************************************************************/
			/*   "$6\r\nfoobar\r\n"													*/
			/************************************************************************/
			case protocol::replyType::REPLY_BULK: //string
			{
				if (commands.size() == 2)
				{
					size_t len = std::stoll(commands.front().substr(1));
					if (len == commands.back().size())
					{
						return std::make_shared<replyImpl>(type, commands.back());
					}
				}

			}
			break;

			/************************************************************************/
			/*  *5\r\n
			:1\r\n
			:2\r\n
			:3\r\n
			:4\r\n
			$6\r\n
			foobar\r\n                                                          */
			/************************************************************************/
			case protocol::replyType::REPLY_MULTI_BULK: //array
			{
				std::shared_ptr<replyImpl> replyMain(std::make_shared<replyImpl>(type,""));
				size_t arrayCount = 0;

				for (auto it = std::next(commands.begin()); it != commands.end(); ++it)
				{
					protocol::replyType subtype = analysisReplyType(*it);

					switch (subtype)
					{
					case protocol::REPLY_STATUS:
					case protocol::REPLY_ERROR:
					case protocol::REPLY_INTEGER:
					{
						replyMain->pushImpl(std::make_shared<replyImpl>(subtype,(*it).substr(1)));
						arrayCount++;
					}
						break;
					case protocol::REPLY_BULK:
					{
						size_t len = std::stoll(it->substr(1));
						auto nex = std::next(it);

						if (nex == commands.end()) break;

						if (len == nex->size())
						{
							replyMain->pushImpl(std::make_shared<replyImpl>(subtype, (*nex).substr(1)));
							arrayCount++;
							it = nex;						
						}
					}
						break;
			
					default:
						break;
					}
				}

				if (std::stoll(commands.front().substr(1)) == arrayCount) return nullptr;

			}
			break;
			default:
				break;
			}

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

			return protocol::replyType::REPLY_UNKNOW;
		}

	private:
	
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

		std::string deserializeBuffer_;
	};
};

#endif