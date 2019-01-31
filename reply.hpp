
#ifndef _CXXREDIS_REPLY_HPP_
#define _CXXREDIS_REPLY_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <memory>
#include <vector>

namespace redis {

	class replyImpl;

	class reply{	
	public:

		reply();
		reply(std::shared_ptr<replyImpl> impl);

		~reply();

		bool isarray() const noexcept;
		bool isinteger() const noexcept;
		bool isstring() const noexcept;
		bool isstatus() const noexcept;
		bool isnil() const noexcept;
		bool iserror() const noexcept;

		long long integer() const;
		std::string string() const;
		std::vector<reply> array() const;


		bool ok() const;

		operator long long();
		operator std::string();

	private:
		std::shared_ptr<replyImpl> impl_;
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "redis/impl/reply.hpp"
#endif

#endif