#ifndef _CXXREDIS_OP_SET_HPP_
#define _CXXREDIS_OP_SET_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

/************************************************************************/
/* �����ĵ�																*/
/* http://redisdoc.com/set/index.html									*/
/************************************************************************/

#include <string>

namespace redis {

	class client;
	class reply;

	namespace container {

		class set {

		public:
			set(client& cli);
			~set();

			/**
			* ����
			* http://redisdoc.com/set/sadd.html
			* ENGLISH
			* https://redis.io/commands/sadd
			*/
			reply sadd(const std::string& key, const std::list<std::string>& members);

			/**
			* ����
			* http://redisdoc.com/set/scard.html
			* ENGLISH
			* https://redis.io/commands/scard
			*/
			reply scard(const std::string& key);

			/**
			* ����
			* http://redisdoc.com/set/sdiff.html
			* ENGLISH
			* https://redis.io/commands/sdiff
			*/
			reply set::sdiff(const std::list<std::string>& keys);

			/**
			* ����
			* http://redisdoc.com/set/sdiffstore.html
			* ENGLISH
			* https://redis.io/commands/sdiffstore
			*/
			reply sdiffstore(const std::string& destination, const std::list<std::string>& keys);

			/**
			* ����
			* http://redisdoc.com/set/sinter.html
			* ENGLISH
			* https://redis.io/commands/sinter
			*/
			reply sinter(const std::list<std::string>& keys);

			/**
			* ����
			* http://redisdoc.com/set/sinterstore.html
			* ENGLISH
			* https://redis.io/commands/sinterstore
			*/
			reply sinterstore(const std::string& destination, const std::list<std::string>& keys);

			/**
			* ����
			* http://redisdoc.com/set/sismember.html
			* ENGLISH
			* https://redis.io/commands/sismember
			*/
			reply sismember(const std::string& key, const std::string& member);

			/**
			* ����
			* http://redisdoc.com/set/smembers.html
			* ENGLISH
			* https://redis.io/commands/smembers
			*/
			reply smembers(const std::string& key);

			/**
			* ����
			* http://redisdoc.com/set/smove.html
			* ENGLISH
			* https://redis.io/commands/smove
			*/
			reply smove(const std::string& source, const std::string& destination, const std::string& member);

			/**
			* ����
			* http://redisdoc.com/set/spop.html
			* ENGLISH
			* https://redis.io/commands/spop
			*/
			reply spop(const std::string& key);

			/**
			* ����
			* http://redisdoc.com/set/srandmember.html
			* ENGLISH
			* https://redis.io/commands/srandmember
			*/
			reply srandmember(const std::string& key,size_t count = 0xffffffff);

			/**
			* ����
			* http://redisdoc.com/set/srem.html
			* ENGLISH
			* https://redis.io/commands/srem
			*/
			reply srem(const std::string& key, const std::list<std::string>& members);

			/**
			* ����
			* http://redisdoc.com/set/sunion.html
			* ENGLISH
			* https://redis.io/commands/sunion
			*/
			reply sunion(const std::list<std::string>& keys);

			/**
			* ����
			* http://redisdoc.com/set/sunionstore.html
			* ENGLISH
			* https://redis.io/commands/sunionstore
			*/
			reply sunionstore(const std::string& destination, const std::list<std::string>& keys);
			/**
			* ����
			* http://redisdoc.com/set/sscan.html
			* ENGLISH
			* https://redis.io/commands/sscan
			*/
			reply sscan(const std::string& key, int cursor = 0, const std::string& matchPattern = "*", int count = 10);
		private:
			client& cli_;
		};
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/set.hpp"
#endif

#endif