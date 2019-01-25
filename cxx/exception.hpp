
#ifndef _CXXREDIS_EXCEPTION_HPP_
#define _CXXREDIS_EXCEPTION_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <exception>
#include <string>

namespace CXXRedis {

	class exception : public std::exception {

	public:
		enum errorCode {

			SOCKET_IO_ERROR,
			SCOKET_IO_EOF,

			PROTOCOL_ERROR,
			FETCH_REPLY_VAL_ERROR,
		};
	public:
		exception(int errCode, const std::string& errStr)
			:errCode_(errCode),
			errStr_(errStr) {}

		virtual const char* what() const noexcept override {
			return errStr_.c_str();
		}
	private:
		int errCode_;
		std::string errStr_;

	};
};

#endif