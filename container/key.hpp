
#ifndef _CXXREDIS_OP_KEY_HPP_
#define _CXXREDIS_OP_KEY_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

/************************************************************************/
/* �����ĵ�																*/
/* http://redisdoc.com/key/index.html									*/
/************************************************************************/

#include <string>

namespace redis {

	class client;
	class reply;

	namespace container {

		class key {

		public:
			key(client& cli);
			~key();

			/**
			* ����
			* http://redisdoc.com/key/del.html
			* ENGLISH
			* https://redis.io/commands/del
			*/
			reply del(const std::list<std::string>& keys);

			/**
			* ����
			* http://redisdoc.com/key/dump.html
			* ENGLISH
			* https://redis.io/commands/dump
			*/
			reply dump(const std::string& k);

			/**
			* ����
			* http://redisdoc.com/key/restore.html
			* ENGLISH
			* https://redis.io/commands/restore
			*/
			reply restore(const std::string& k, time_t ttl, const std::string& serializedValue, bool replace = false);

			/**
			* ����
			* http://redisdoc.com/key/exists.html
			* ENGLISH
			* https://redis.io/commands/exists
			*/
			reply exists(const std::string& k);

			/**
			* ����
			* http://redisdoc.com/key/expire.html
			* ENGLISH
			* https://redis.io/commands/expire
			*/
			reply expire(const std::string& k, time_t second);
			/**
			* ����
			* http://redisdoc.com/key/expireat.html
			* ENGLISH
			* https://redis.io/commands/expireat
			*/
			reply expireat(const std::string& k, time_t timestamp);
			/**
			* ����
			* http://redisdoc.com/key/pexpireat.html
			* ENGLISH
			* https://redis.io/commands/pexpireat
			*/
			reply pexpireat(const std::string& k, time_t millisecondsTimestamp);
			/**
			* ����
			* http://redisdoc.com/key/pexpire.html
			* ENGLISH
			* https://redis.io/commands/pexpire
			*/
			reply pexpire(const std::string& k, time_t milliseconds);

			/**
			* ����
			* http://redisdoc.com/key/persist.html
			* ENGLISH
			* https://redis.io/commands/persist
			*/
			reply persist(const std::string& k);

			/**
			* ����
			* http://redisdoc.com/key/keys.html
			* ENGLISH
			* https://redis.io/commands/keys
			*/
			reply keys(const std::string& pattern);
			reply keys();
			/**
			* ����
			* http://redisdoc.com/key/migrate.html
			* ENGLISH
			* https://redis.io/commands/migrate
			*/
			reply migrate(const std::string& host, int port, const std::string& k, int db, time_t milliseconds);
			/**
			* ����
			* http://redisdoc.com/key/move.html
			* ENGLISH
			* https://redis.io/commands/move
			*/
			reply move(const std::string& k, int db);
			/**
			* ����
			* http://redisdoc.com/key/object.html
			* ENGLISH
			* https://redis.io/commands/object
			*/
			reply object(const std::string& subcommand, const std::string& k);

			reply objectRefcount(const std::string& k);
			reply objectIdleTime(const std::string& k);
			reply objectEncoding(const std::string& k);

			/**
			* ����
			* http://redisdoc.com/key/ttl.html
			* ENGLISH
			* https://redis.io/commands/ttl
			*/
			reply ttl(const std::string& k);

			/**
			* ����
			* http://redisdoc.com/key/pttl.html
			* ENGLISH
			* https://redis.io/commands/pttl
			*/
			reply pttl(const std::string& k);

			/**
			* ����
			* http://redisdoc.com/key/randomkey.html
			* ENGLISH
			* https://redis.io/commands/randomkey
			*/
			reply randomkey();
			/**
			* ����
			* http://redisdoc.com/key/rename.html
			* ENGLISH
			* https://redis.io/commands/rename
			*/
			reply rename(const std::string& k, const std::string& newkey);
			/**
			* ����
			* http://redisdoc.com/key/renamenx.html
			* ENGLISH
			* https://redis.io/commands/renamenx
			*/
			reply renamenx(const std::string& k, const std::string& newkey);
			/**
			* ����
			* http://redisdoc.com/key/sort.html
			* ENGLISH
			* https://redis.io/commands/sort
			*/
			reply sort(const std::string& k, const std::string& pattern);

			/**
			* ����
			* http://redisdoc.com/key/type.html
			* ENGLISH
			* https://redis.io/commands/type
			*/
			reply type(const std::string& k);

			/**
			* ����
			* http://redisdoc.com/key/scan.html
			* ENGLISH
			* https://redis.io/commands/scan
			*/
			reply scan(int cursor, const std::string& matchPattern = "*", int count = 10);

		private:
			client& cli_;
		};
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/key.hpp"
#endif

#endif