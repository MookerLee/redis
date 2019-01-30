
#include "redis/client.hpp"

namespace redis {
	namespace container {

		key::key(client& cli)
			:cli_(cli)
		{

		}
		key::~key()
		{

		}
		redis::reply key::del(const std::list<std::string>& keys)
		{
			std::list<std::string> commands{"DEL"};
			commands.insert(commands.end(), keys.begin(), keys.end());

			return cli_.sendListCommand(commands);
		}

		reply key::dump(const std::string& k)
		{
			return cli_.sendSafeCommand("DUMP", k);
		}
		redis::reply key::exists(const std::string& k)
		{
			return cli_.sendSafeCommand("EXISTS",k);
		}
		reply key::expire(const std::string& k, time_t second)
		{
			return cli_.sendSafeCommand("EXPIRE", k, second);
		}
		redis::reply key::expireat(const std::string& k, time_t timestamp)
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
		redis::reply key::migrate(const std::string& host, int port, const std::string& k, int db, time_t milliseconds)
		{
			return cli_.sendSafeCommand("MIGRATE", host, port, k, db, milliseconds);
		}
		redis::reply key::move(const std::string& k, int db)
		{
			return cli_.sendSafeCommand("MOVE", k, db);
		}
		redis::reply key::objectRefcount(const std::string& k)
		{
			return object("REFCOUNT", k);
		}
		redis::reply key::objectIdleTime(const std::string& k)
		{
			return object("IDLETIME", k);
		}
		redis::reply key::objectEncoding(const std::string& k)
		{
			return object("ENCODING", k);
		}
		redis::reply key::persist(const std::string& k)
		{
			return cli_.sendSafeCommand("PERSIST", k);
		}
		redis::reply key::pexpire(const std::string& k, time_t milliseconds)
		{
			return cli_.sendSafeCommand("PEXPIRE", k, milliseconds);
		}
		redis::reply key::pexpireat(const std::string& k, time_t millisecondsTimestamp)
		{
			return cli_.sendSafeCommand("PEXPIREAT", k, millisecondsTimestamp);
		}
		redis::reply key::ttl(const std::string& k)
		{
			return cli_.sendSafeCommand("TTL", k);
		}
		redis::reply key::pttl(const std::string& k)
		{
			return cli_.sendSafeCommand("PTTL", k);
		}
		redis::reply key::randomkey()
{
			return cli_.sendSafeCommand("RANDOMKEY");
		}
		redis::reply key::rename(const std::string& k, const std::string& newkey)
		{
			return cli_.sendSafeCommand("RENAME", k, newkey);
		}
		redis::reply key::renamenx(const std::string& k, const std::string& newkey)
		{
			return cli_.sendSafeCommand("RENAMENX", k, newkey);
		}
		redis::reply key::restore(const std::string& k, time_t ttl, const std::string& serializedValue, bool replace /*= false*/)
		{
			std::list<std::string> commands{ "RESTORE",k };
			commands.push_back(std::to_string(ttl));
			commands.push_back(serializedValue);
			if (replace) commands.push_back("REPLACE");
			
			return cli_.sendListCommand(commands);
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
		reply key::object(const std::string& subcommand, const std::string& k)
		{
			return cli_.sendSafeCommand("OBJECT", subcommand, k);
		}
	};
};