#ifndef _REDIS_ADVANCE_HYPERLOGLOG_HPP_
#define _REDIS_ADVANCE_HYPERLOGLOG_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

/************************************************************************/
/* 在线文档																*/
/* http://redisdoc.com/hyperloglog/index.html							*/
/************************************************************************/

namespace redis {

	class client;
	class reply;

	namespace advance {

		class hyperloglog {
		public:
			hyperloglog(client& cli);
			~hyperloglog();

			/**
			* 中文
			* http://redisdoc.com/hyperloglog/pfadd.html
			* ENGLISH
			* https://redis.io/commands/pfadd
			*/
			reply pfadd(const std::string& key, const std::list<std::string>& elements);

			/**
			* 中文
			* http://redisdoc.com/hyperloglog/pfcount.html
			* ENGLISH
			* https://redis.io/commands/pfcount
			*/
			reply pfcount(const std::list<std::string>& keys);

			/**
			* 中文
			* http://redisdoc.com/hyperloglog/pfmerge.html
			* ENGLISH
			* https://redis.io/commands/pfmerge
			*/
			reply pfmerge(const std::string& key, const std::list<std::string>& sourcekeys);
		private:
			client& cli_;
		};
	};
};
#if !defined(CORE_ONLY_HEADER)
#include "impl/hyperloglog.hpp"
#endif

#endif