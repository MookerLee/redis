
#ifndef _CXXREDIS_CONNECTION_HPP_
#define _CXXREDIS_CONNECTION_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <string>
#include <memory>

namespace CXXRedis {

	class connectionImpl;

	class connection {
	public:
		connection();
		~connection();
	public:
		void connect(const std::string& host, int port);
		void send(const void* buff, size_t bytes);
		std::string read();
	private:
		std::shared_ptr<connectionImpl> impl_;
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/connection.hpp"
#endif

#endif