

#ifndef _CXXREDIS_PROTOCOL_HPP_
#define _CXXREDIS_PROTOCOL_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <memory>
#include <string>

namespace CXXRedis {

	class protocolImpl;
	class reply;

	class protocol {
	public:

		enum replyType
		{
			REPLY_UNKNOW,		//未知类型
			REPLY_STATUS,		//状态回复（status reply）的第一个字节是 "+"
			REPLY_ERROR,		//错误回复（error reply）的第一个字节是 "-"
			REPLY_INTEGER,		//整数回复（integer reply）的第一个字节是 ":"
			REPLY_BULK,			//批量回复（bulk reply）的第一个字节是 "$"
			REPLY_MULTI_BULK,	//多条批量回复（multi bulk reply）的第一个字节是 "*"
		};

		protocol();
		~protocol();

		std::string serializeSimpleCommand(const std::string& simpleCommand);

		reply feedBuffer(const std::string& readString);

	private:
		std::shared_ptr<protocolImpl> impl_;
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/protocol.hpp"
#endif

#endif