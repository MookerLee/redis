
#ifndef _REDIS_CONTAINER_STRING_HPP_
#define _REDIS_CONTAINER_STRING_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

/************************************************************************/
/* 在线文档																*/
/* http://redisdoc.com/string/index.html								*/
/************************************************************************/

#include <string>
#include <map>

namespace redis {

	class client;
	class reply;

	namespace container {

		class string {

		public:
			string(client& cli);
			~string();

			/**
			* 中文
			* http://redisdoc.com/string/append.html
			* ENGLISH
			* https://redis.io/commands/append
			*/
			reply append(const std::string& key, const std::string& str);

			/**
			* 中文
			* http://redisdoc.com/string/bitcount.html
			* ENGLISH
			* https://redis.io/commands/bitcount
			*/
			reply bitcount(const std::string& key, int start = 0, int end = -1);

			/**
			* 中文
			* http://redisdoc.com/string/bitop.html
			* ENGLISH
			* https://redis.io/commands/bitop
			*/
			reply bitop(const std::string& operation, const std::string& destkey,const std::list<std::string>& keys);
			reply bitopAnd(const std::string& destkey, const std::list<std::string>& keys);
			reply bitopOr(const std::string& destkey, const std::list<std::string>& keys);
			reply bitopXor(const std::string& destkey, const std::list<std::string>& keys);
			reply bitopNot(const std::string& destkey, const std::string& key);

			/**
			* 中文
			* http://redisdoc.com/string/getbit.html
			* ENGLISH
			* https://redis.io/commands/getbit
			*/
			reply getbit(const std::string& key, int offset);

			/**
			* 中文
			* http://redisdoc.com/string/setbit.html
			* ENGLISH
			* https://redis.io/commands/setbit
			*/
			reply setbit(const std::string& key, int offset, int value);

			/**
			* 中文
			* http://redisdoc.com/string/decr.html
			* ENGLISH
			* https://redis.io/commands/decr
			*/
			reply decr(const std::string& key);
			
			/**
			* 中文
			* http://redisdoc.com/string/decrby.html
			* ENGLISH
			* https://redis.io/commands/decrby
			*/
			reply decrby(const std::string& key, long long decrement);
			
			/**
			* 中文
			* http://redisdoc.com/string/incr.html
			* ENGLISH
			* https://redis.io/commands/incr
			*/
			reply incr(const std::string& key);

			/**
			* 中文
			* http://redisdoc.com/string/incrby.html
			* ENGLISH
			* https://redis.io/commands/incrby
			*/
			reply incrby(const std::string& key, long long increment);

			/**
			* 中文
			* http://redisdoc.com/string/incrbyfloat.html
			* ENGLISH
			* https://redis.io/commands/incrbyfloat
			*/
			reply incrbyfloat(const std::string& key, const std::string&  increment);

			/**
			* 中文
			* http://redisdoc.com/string/get.html
			* ENGLISH
			* https://redis.io/commands/get
			*/
			reply get(const std::string& key);

			/**
			* 中文
			* http://redisdoc.com/string/mget.html
			* ENGLISH
			* https://redis.io/commands/mget
			*/
			reply mget(const std::list<std::string>& keys);

			/**
			* 中文
			* http://redisdoc.com/string/getrange.html
			* ENGLISH
			* https://redis.io/commands/getrange
			*/
			reply getrange(const std::string& key,int start = 0,int end = -1);

			/**
			* 中文
			* http://redisdoc.com/string/getset.html
			* ENGLISH
			* https://redis.io/commands/getset
			*/
			reply getset(const std::string& key, const std::string& value);

			/**
			* 中文
			* http://redisdoc.com/string/mset.html
			* ENGLISH
			* https://redis.io/commands/mset
			*/
			reply mset(const std::multimap<std::string,std::string>& keyValues);

			/**
			* 中文
			* http://redisdoc.com/string/msetnx.html
			* ENGLISH
			* https://redis.io/commands/msetnx
			*/
			reply msetnx(const std::multimap<std::string, std::string>& keyValues);

			/**
			* 中文
			* http://redisdoc.com/string/psetex.html
			* ENGLISH
			* https://redis.io/commands/psetex
			*/
			reply psetex(const std::string& key, time_t milliseconds, const std::string& value);

			/**
			* 中文
			* http://redisdoc.com/string/set.html
			* ENGLISH
			* https://redis.io/commands/set
			*/
			reply set(const std::string& key, const std::string& value);

			/**
			* 中文
			* http://redisdoc.com/string/setex.html
			* ENGLISH
			* https://redis.io/commands/setex
			*/
			reply setex(const std::string& key, time_t seconds, const std::string& value);

			/**
			* 中文
			* http://redisdoc.com/string/setnx.html
			* ENGLISH
			* https://redis.io/commands/setnx
			*/
			reply setnx(const std::string& key, const std::string& value);

			/**
			* 中文
			* http://redisdoc.com/string/setrange.html
			* ENGLISH
			* https://redis.io/commands/setrange
			*/
			reply setrange(const std::string& key,int offset, const std::string& value);

			/**
			* 中文
			* http://redisdoc.com/string/strlen.html
			* ENGLISH
			* https://redis.io/commands/strlen
			*/
			reply strlen(const std::string& key);

		private:
			client& cli_;
		};
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/string.hpp"
#endif

#endif