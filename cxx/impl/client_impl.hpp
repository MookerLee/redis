#pragma once

#ifndef _REDIS_CLIENT_IMPL_H_
#define _REDIS_CLIENT_IMPL_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "redis/cxx/exception.hpp"
#include "redis/cxx/reply.hpp"
#include "redis/cxx/connection.hpp"
#include "redis/cxx/protocol.hpp"

#include "reply_impl.hpp"

#include <string>
#include <cassert>


namespace CXXRedis {

class clientImpl {

public:

	clientImpl(){}
	~clientImpl() {}

	void connect(const std::string& ip, int port) 
	{
		con_.connect(ip, port);
	}

	reply send(const std::string& cmd)
	{
		std::string serializeCommand = protocol_.serializeSimpleCommand(cmd);
		con_.send(serializeCommand.c_str(), serializeCommand.length());

		while ((protocol_.feedBuffer(con_.read())) == false) {}

		return protocol_.fetch();
	}

private:
	
	connection con_;
	protocol protocol_;
};
};

#endif