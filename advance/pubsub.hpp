
#ifndef _REDIS_ADVANCE_PUBSUB_HPP_
#define _REDIS_ADVANCE_PUBSUB_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

/************************************************************************/
/* 在线文档																*/
/* http://redisdoc.com/pub_sub/index.html								*/
/************************************************************************/

namespace redis {

	class client;
	class reply;

	namespace advance {

		class pubsub {
		public:
			pubsub(client& cli);
			~pubsub();

			/**
			* 中文
			* http://redisdoc.com/pub_sub/psubscribe.html
			* ENGLISH
			* https://redis.io/commands/psubscribe
			*/
			reply psubscribe(const std::list<std::string>& patterns);

			/**
			* 中文
			* http://redisdoc.com/pub_sub/publish.html
			* ENGLISH
			* https://redis.io/commands/publish
			*/
			reply publish(const std::string& channel, const std::string& message);

			/**
			* 中文
			* http://redisdoc.com/pub_sub/pubsub.html
			* ENGLISH
			* https://redis.io/commands/pubsub
			*/
			reply pubSub(const std::string& subcommand, const std::list<std::string>& arguments);

			/**
			* 中文
			* http://redisdoc.com/pub_sub/punsubscribe.html
			* ENGLISH
			* https://redis.io/commands/punsubscribe
			*/
			reply punsubscribe(const std::list<std::string>& patterns);

			/**
			* 中文
			* http://redisdoc.com/pub_sub/subscribe.html
			* ENGLISH
			* https://redis.io/commands/subscribe
			*/
			reply subscribe(const std::list<std::string>& channels);

			/**
			* 中文
			* http://redisdoc.com/pub_sub/unsubscribe.html
			* ENGLISH
			* https://redis.io/commands/unsubscribe
			*/
			reply unsubscribe(const std::list<std::string>& channels);
		private:
			client& cli_;
		};
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/pubsub.hpp"
#endif

#endif