#ifndef _CXXREDIS_OP_LIST_HPP_
#define _CXXREDIS_OP_LIST_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

/************************************************************************/
/* 在线文档																*/
/* http://redisdoc.com/list/index.html									*/
/************************************************************************/

#include <string>

namespace redis {

	class client;
	class reply;

	namespace container {
		class list {
		public:
			list(client& cli);
			~list();

			/**
			* 中文
			* http://redisdoc.com/list/blpop.html
			* ENGLISH
			* https://redis.io/commands/blpop
			*/
			reply blpop(const std::list<std::string>& keys,time_t timeout = 0);

			/**
			* 中文
			* http://redisdoc.com/list/brpop.html
			* ENGLISH
			* https://redis.io/commands/brpop
			*/
			reply brpop(const std::list<std::string>& keys, time_t timeout= 0);

			/**
			* 中文
			* http://redisdoc.com/list/brpoplpush.html
			* ENGLISH
			* https://redis.io/commands/brpoplpush
			*/
			reply brpoplpush(const std::string& source, const std::string& destination, time_t timeout = 0);

			/**
			* 中文
			* http://redisdoc.com/list/lindex.html
			* ENGLISH
			* https://redis.io/commands/lindex
			*/
			reply lindex(const std::string& key, size_t idx);

			/**
			* 中文
			* http://redisdoc.com/list/linsert.html
			* ENGLISH
			* https://redis.io/commands/linsert
			*/
			reply linsert(const std::string& key, 
				const std::string& subcommand, 
				const std::string& pivot, 
				const std::string& value);

			reply linsertBefore(const std::string& key, const std::string& pivot, const std::string& value);
			reply linsertAfter(const std::string& key, const std::string& pivot, const std::string& value);

			/**
			* 中文
			* http://redisdoc.com/list/llen.html
			* ENGLISH
			* https://redis.io/commands/llen
			*/
			reply llen(const std::string& key);

			/**
			* 中文
			* http://redisdoc.com/list/lpop.html
			* ENGLISH
			* https://redis.io/commands/lpop
			*/
			reply lpop(const std::string& key);

			/**
			* 中文
			* http://redisdoc.com/list/lpush.html
			* ENGLISH
			* https://redis.io/commands/lpush
			*/
			reply lpush(const std::string& key, const std::list<std::string>& values);

			/**
			* 中文
			* http://redisdoc.com/list/lpushx.html
			* ENGLISH
			* https://redis.io/commands/lpushx
			*/
			reply lpushx(const std::string& key, const std::list<std::string>& values);

			/**
			* 中文
			* http://redisdoc.com/list/lrange.html
			* ENGLISH
			* https://redis.io/commands/lrange
			*/
			reply lrange(const std::string& key, int start = 0, int stop = -1);

			/**
			* 中文
			* http://redisdoc.com/list/lrem.html
			* ENGLISH
			* https://redis.io/commands/lrem
			*/
			reply lrem(const std::string& key, size_t count, const std::string& value);

			/**
			* 中文
			* http://redisdoc.com/list/lset.html
			* ENGLISH
			* https://redis.io/commands/lset
			*/
			reply lset(const std::string& key, size_t index, const std::string& value);

			/**
			* 中文
			* http://redisdoc.com/list/ltrim.html
			* ENGLISH
			* https://redis.io/commands/ltrim
			*/
			reply ltrim(const std::string& key, int start = 0, int stop = -1);

			/**
			* 中文
			* http://redisdoc.com/list/rpop.html
			* ENGLISH
			* https://redis.io/commands/rpop
			*/
			reply rpop(const std::string& key);

			/**
			* 中文
			* http://redisdoc.com/list/rpoplpush.html
			* ENGLISH
			* https://redis.io/commands/rpoplpush
			*/
			reply rpoplpush(const std::string& source, const std::string& destination);

			/**
			* 中文
			* http://redisdoc.com/list/rpush.html
			* ENGLISH
			* https://redis.io/commands/rpush
			*/
			reply rpush(const std::string& key, const std::list<std::string>& values);

			/**
			* 中文
			* http://redisdoc.com/list/rpushx.html
			* ENGLISH
			* https://redis.io/commands/rpushx
			*/
			reply rpushx(const std::string& key, const std::string& value);
		private:
			client& cli_;
		};
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/list.hpp"
#endif

#endif
