
#ifndef _REDIS_ADVANCE_TRANSACTION_HPP_
#define _REDIS_ADVANCE_TRANSACTION_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

/************************************************************************/
/* �����ĵ�																*/	
/* http://redisdoc.com/transaction/index.html                           */
/************************************************************************/
namespace redis {

	class client;
	class reply;

	namespace advance {

		class transaction {
		public:
			transaction(client& cli);
			~transaction();

			/**
			* ����
			* http://redisdoc.com/transaction/discard.html
			* ENGLISH
			* https://redis.io/commands/discard
			*/
			reply discard();

			/**
			* ����
			* http://redisdoc.com/transaction/exec.html
			* ENGLISH
			* https://redis.io/commands/exec
			*/
			reply exec();

			/**
			* ����
			* http://redisdoc.com/transaction/multi.html
			* ENGLISH
			* https://redis.io/commands/multi
			*/
			reply multi();

			/**
			* ����
			* http://redisdoc.com/transaction/unwatch.html
			* ENGLISH
			* https://redis.io/commands/unwatch
			*/
			reply unwatch();

			/**
			* ����
			* http://redisdoc.com/transaction/watch.html
			* ENGLISH
			* https://redis.io/commands/watch
			*/
			reply watch(const std::list<std::string>& keys);
		private:
			client& cli_;
		};
	};
};
#if !defined(CORE_ONLY_HEADER)
#include "impl/transaction.hpp"
#endif

#endif