
#ifndef _REDIS_REPLY_H
#define _REDIS_REPLY_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <memory>


namespace CXXRedis {

	class responseImpl;

	class response{	
	public:

		response();
		response(std::shared_ptr<responseImpl> impl);

		~response();

		bool isArray() const noexcept;
		bool isInteger() const noexcept;
		bool isString() const noexcept;

		long long asInteger() const;
		std::string asString() const;

		std::vector<response> asArray() const;

		bool empty() const noexcept;

		operator bool();
		operator long long();
		operator std::string();

	private:
		std::shared_ptr<responseImpl> impl_;
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "redis/cxx/impl/response.hpp"
#endif

#endif