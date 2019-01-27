
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

			PROTOCOL_ERROR,		//协议解析错误

			REPLY_ERROR,		//服务器返回ERROR
			REPLY_VAL_NONEXIST, //访问的KEY不存在
			REPLY_VAL_ERROR,	//取值错误

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