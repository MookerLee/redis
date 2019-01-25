
#ifndef _CXXREDIS_REPLY_HPP_
#define _CXXREDIS_REPLY_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <memory>


namespace CXXRedis {

	class replyImpl;

	class reply{	
	public:

		reply();
		reply(std::shared_ptr<replyImpl> impl);

		~reply();

		bool isArray() const noexcept;
		bool isInteger() const noexcept;
		bool isString() const noexcept;

		long long asInteger() const;
		std::string asString() const;

		std::vector<reply> asArray() const;

		bool empty() const noexcept;

		operator bool();
		operator long long();
		operator std::string();

	private:
		std::shared_ptr<replyImpl> impl_;
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "redis/cxx/impl/reply.hpp"
#endif

#endif