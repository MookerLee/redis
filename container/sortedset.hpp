

#ifndef _REDIS_CONTAINER_SORTED_SET_HPP_
#define _REDIS_CONTAINER_SORTED_SET_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

/************************************************************************/
/* 在线文档																*/
/* http://redisdoc.com/sorted_set/index.html							*/
/************************************************************************/

#include <map>
#include <list>

namespace redis {

	class client;
	class reply;

	namespace container {
		class sortedset {
		public:
			sortedset(client& cli);
			~sortedset();

			/**
			* 中文
			* http://redisdoc.com/sorted_set/zadd.html
			* ENGLISH
			* https://redis.io/commands/zadd
			*/
			reply zadd(const std::string& key, const std::multimap<long long,std::string>& scoreMembers);

			/**
			* 中文
			* http://redisdoc.com/sorted_set/zcard.html
			* ENGLISH
			* https://redis.io/commands/zcard
			*/
			reply zcard(const std::string& key);

			/**
			* 中文
			* http://redisdoc.com/sorted_set/zcount.html
			* ENGLISH
			* https://redis.io/commands/zcount
			*/
			reply zcount(const std::string& key, const std::string& min = "-inf", const std::string& max = "+inf");

			/**
			* 中文
			* http://redisdoc.com/sorted_set/zincrby.html
			* ENGLISH
			* https://redis.io/commands/zincrby
			*/
			reply zincrby(const std::string& key, const std::string& increment, const std::string& member);

			/**
			* 中文
			* http://redisdoc.com/sorted_set/zrange.html
			* ENGLISH
			* https://redis.io/commands/zrange
			*/
			reply zrange(const std::string& key, int start = 0, int stop = -1, bool withscores = true );

			/**
			* 中文
			* http://redisdoc.com/sorted_set/zrangebyscore.html
			* ENGLISH
			* https://redis.io/commands/zrangebyscore
			*/
			reply zrangebyscore(const std::string& key, 
				const std::string& min = "-inf", 
				const std::string& max = "+inf",
				bool withscores = true,
				const std::pair<int,int>& limit = std::make_pair(0,1000)/*first offset ,second count */);

			/**
			* 中文
			* http://redisdoc.com/sorted_set/zrank.html
			* ENGLISH
			* https://redis.io/commands/zrank
			*/
			reply zrank(const std::string& key, const std::string& member);

			/**
			* 中文
			* http://redisdoc.com/sorted_set/zrem.html
			* ENGLISH
			* https://redis.io/commands/zrem
			*/
			reply zrem(const std::string& key, const std::list<std::string>& members);

			/**
			* 中文
			* http://redisdoc.com/sorted_set/zremrangebyrank.html
			* ENGLISH
			* https://redis.io/commands/zremrangebyrank
			*/
			reply zremrangebyrank(const std::string& key, int start = 0, int stop = -1);

			/**
			* 中文
			* http://redisdoc.com/sorted_set/zremrangebyscore.html
			* ENGLISH
			* https://redis.io/commands/zremrangebyscore
			*/
			reply zremrangebyscore(const std::string& key, const std::string& min = "-inf", const std::string& max = "+inf");

			/**
			* 中文
			* http://redisdoc.com/sorted_set/zrevrange.html
			* ENGLISH
			* https://redis.io/commands/zrevrange
			*/
			reply zrevrange(const std::string& key, int start = 0, int stop = -1, bool withscores = true);

			/**
			* 中文
			* http://redisdoc.com/sorted_set/zrevrangebyscore.html
			* ENGLISH
			* https://redis.io/commands/zrevrangebyscore
			*/
			reply zrevrangebyscore(const std::string& key, 
				const std::string& max = "+inf", 
				const std::string& min = "-inf",
				bool withscores = true,
				const std::pair<int, int>& limit = std::make_pair(0, 1000)/*first offset ,second count */);

			/**
			* 中文
			* http://redisdoc.com/sorted_set/zrevrank.html
			* ENGLISH
			* https://redis.io/commands/zrevrank
			*/
			reply zrevrank(const std::string& key, const std::string& member);

			/**
			* 中文
			* http://redisdoc.com/sorted_set/zscore.html
			* ENGLISH
			* https://redis.io/commands/zscore
			*/
			reply zscore(const std::string& key, const std::string& member);

			/**
			* 中文
			* http://redisdoc.com/sorted_set/zunionstore.html
			* ENGLISH
			* https://redis.io/commands/zunionstore
			*/
			reply zunionstore(const std::string& destination,
				const std::list<std::string>& keys,
				const std::list<std::string>& weights = {},
				const std::string& aggregate = "");

			/**
			* 中文
			* http://redisdoc.com/sorted_set/zinterstore.html
			* ENGLISH
			* https://redis.io/commands/zinterstore
			*/
			reply zinterstore(const std::string& destination,
				const std::list<std::string>& keys,
				const std::list<std::string>& weights = {},
				const std::string& aggregate = "");


			/**
			* 中文
			* http://redisdoc.com/sorted_set/zscan.html
			* ENGLISH
			* https://redis.io/commands/zscan
			*/
			reply zscan(const std::string& key, int cursor = 0, const std::string& matchPattern = "*", int count = 10);

			/**
			* 中文
			* http://redisdoc.com/sorted_set/zrangebylex.html
			* ENGLISH
			* https://redis.io/commands/zrangebylex
			*/
			reply zrangebylex(const std::string& key, 
				const std::string& min = "-inf", 
				const std::string& max = "+inf",
				const std::pair<int, int>& limit = std::make_pair(0, 1000)/*first offset ,second count */);

			/**
			* 中文
			* http://redisdoc.com/sorted_set/zlexcount.html
			* ENGLISH
			* https://redis.io/commands/zlexcount
			*/
			reply zlexcount(const std::string& key,
				const std::string& min = "-inf",
				const std::string& max = "+inf");
			/**
			* 中文
			* http://redisdoc.com/sorted_set/zremrangebylex.html
			* ENGLISH
			* https://redis.io/commands/zremrangebylex
			*/
			reply zremrangebylex(const std::string& key,
				const std::string& min = "-inf",
				const std::string& max = "+inf");
		private:
			client& cli_;
		};
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/sortedset.hpp"
#endif

#endif