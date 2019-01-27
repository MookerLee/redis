
#include "redis/cxx/client.hpp"

namespace CXXRedis {
	namespace op {

		key::key(client& cli)
			:cli_(cli)
		{

		}
		key::~key()
		{

		}
		template <class... Args>
		long long key::del(Args... keys)
		{
			return cli_.sendSafeCommand("DEL", keys...).asInteger();
		}

		reply key::dump(const std::string& k)
		{
			return cli_.sendSafeCommand("DUMP", k);
		}
		bool key::exists(const std::string& k)
		{
			return cli_.sendSafeCommand("EXISTS",k);
		}
		bool key::expire(const std::string& k, int second)
		{
			return cli_.sendSafeCommand("EXPIRE", k, second);
		}
		bool key::expireat(const std::string& k, time_t timestamp)
		{
			return cli_.sendSafeCommand("EXPIREAT", k, timestamp);
		}
		reply key::keys(const std::string& pattern)
		{
			return cli_.sendSafeCommand("KEYS", pattern);
		}
		reply key::keys()
		{
			return keys("*");
		}
		void key::migrate(const std::string& host, int port, const std::string& k, int db, time_t milliseconds)
		{
			cli_.sendSafeCommand("MIGRATE", host, port, k, db, milliseconds);
		}
		bool key::move(const std::string& k, int db)
		{
			return cli_.sendSafeCommand("MOVE", k, db);
		}
		long long key::objectRefcount(const std::string& k)
		{
			return object("REFCOUNT", k).asInteger();
		}
		long long key::objectIdleTime(const std::string& k)
		{
			return object("IDLETIME", k).asInteger();
		}
		std::string key::objectEncoding(const std::string& k)
		{
			return object("ENCODING", k).asString();
		}
		bool key::persist(const std::string& k)
		{
			return cli_.sendSafeCommand("PERSIST", k);
		}
		bool key::pexpire(const std::string& k, time_t milliseconds)
		{
			return cli_.sendSafeCommand("PEXPIRE", k, milliseconds);
		}
		bool key::pexpireat(const std::string& k, time_t millisecondsTimestamp)
		{
			return cli_.sendSafeCommand("PEXPIREAT", k, millisecondsTimestamp);
		}
		long long key::ttl(const std::string& k)
		{
			return cli_.sendSafeCommand("TTL", k).asInteger();
		}
		long long key::pttl(const std::string& k)
		{
			return cli_.sendSafeCommand("PTTL", k).asInteger();
		}
		std::string key::randomKey()
		{
			return cli_.sendSafeCommand("RANDOMKEY").asString();
		}
		void key::rename(const std::string& k, const std::string& newkey)
		{
			cli_.sendSafeCommand("RENAME", k, newkey);
		}
		bool key::renameEx(const std::string& k, const std::string& newkey)
		{
			return cli_.sendSafeCommand("RENAMENX", k, newkey);
		}
		void key::restore(const std::string& k, time_t ttl, const std::string& serializedValue)
		{
			cli_.sendSafeCommand("RESTORE", k, ttl, serializedValue);
		}
		reply key::sort(const std::string& k, const std::string& pattern)
		{
			return cli_.sendSafeCommand("SORT", k, pattern);
		}
		reply key::type(const std::string& k)
		{
			return cli_.sendSafeCommand("TYPE", k);
		}
		reply key::scan(int cursor, const std::string& matchPattern /* = "*" */, int count /* = 10 */)
		{
			return cli_.sendSafeCommand("SCAN", cursor, "MATCH", matchPattern, "COUNT", count);
		}
		reply key::object(const std::string& subcmd, const std::string& k)
		{
			return cli_.sendSafeCommand("OBJECT", subcmd, k);
		}
	};
};