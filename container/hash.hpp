#ifndef _CXXREDIS_OP_HASH_HPP_
#define _CXXREDIS_OP_HASH_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

/************************************************************************/
/* 在线文档																*/
/* http://redisdoc.com/hash/index.html									*/
/************************************************************************/

#include <string>

namespace redis {

	class client;
	class reply;

	namespace container {

		class hash {
		public:
			hash(client& cli);
			~hash();

			/**
			* 中文
			* http://redisdoc.com/hash/hdel.html
			* ENGLISH
			* https://redis.io/commands/hdel
			*/
			reply hdel(const std::string& key, const std::list<std::string>& fields);

			/**
			* 中文
			* http://redisdoc.com/hash/hexist.html
			* ENGLISH
			* https://redis.io/commands/hexist
			*/
			reply hexist(const std::string& key, const std::string& field);

			/**
			* 中文
			* http://redisdoc.com/hash/hget.html
			* ENGLISH
			* https://redis.io/commands/hget
			*/
			reply hget(const std::string& key, const std::string& field);

			/**
			* 中文
			* http://redisdoc.com/hash/hgetall.html
			* ENGLISH
			* https://redis.io/commands/hgetall
			*/
			reply hgetall(const std::string& key);

			/**
			* 中文
			* http://redisdoc.com/hash/hincrby.html
			* ENGLISH
			* https://redis.io/commands/hincrby
			*/
			reply hincrby(const std::string& key, const std::string& field, long long increment);

			/**
			* 中文
			* http://redisdoc.com/hash/hincrbyfloat.html
			* ENGLISH
			* https://redis.io/commands/hincrbyfloat
			*/
			reply hincrbyfloat(const std::string& key, const std::string& field, double increment);

			/**
			* 中文
			* http://redisdoc.com/hash/hkeys.html
			* ENGLISH
			* https://redis.io/commands/hkeys
			*/
			reply hkeys(const std::string& key);

			/**
			* 中文
			* http://redisdoc.com/hash/hlen.html
			* ENGLISH
			* https://redis.io/commands/hlen
			*/
			reply hlen(const std::string& key);

			/**
			* 中文
			* http://redisdoc.com/hash/hmget.html
			* ENGLISH
			* https://redis.io/commands/hmget
			*/
			reply hmget(const std::string& key, const std::list<std::string>&  fields);

			/**
			* 中文
			* http://redisdoc.com/hash/hmset.html
			* ENGLISH
			* https://redis.io/commands/hmset
			*/
			reply hmset(const std::string& key, const std::multimap<std::string, std::string>& fieldValues);

			/**
			* 中文
			* http://redisdoc.com/hash/hset.html
			* ENGLISH
			* https://redis.io/commands/hset
			*/
			reply hset(const std::string& key, const std::string& field, const std::string& value);

			/**
			* 中文
			* http://redisdoc.com/hash/hsetnx.html
			* ENGLISH
			* https://redis.io/commands/hsetnx
			*/
			reply hsetnx(const std::string& key, const std::string& field, const std::string& value);

			/**
			* 中文
			* http://redisdoc.com/hash/hvals.html
			* ENGLISH
			* https://redis.io/commands/hvals
			*/
			reply hvals(const std::string& key);

			/**
			* 中文
			* http://redisdoc.com/hash/hscan.html
			* ENGLISH
			* https://redis.io/commands/hscan
			*/
			reply hscan(const std::string& key, int cursor = 0, const std::string& matchPattern = "*", int count = 10);

			/**
			* 中文
			* http://redisdoc.com/hash/hstrlen.html
			* ENGLISH
			* https://redis.io/commands/hstrlen
			*/
			reply hstrlen(const std::string& key, const std::string& field);
		private:
			client& cli_;
		};
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/hash.hpp"
#endif

#endif