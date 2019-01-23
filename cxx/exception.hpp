#pragma once

#include <exception>
#include <string>

namespace CXXRedis {

	class exception : public std::exception {

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
