
#include "redis/client.hpp"

namespace redis{
	namespace container {
		set::set(client& cli)
			:cli_(cli)
		{

		}
		set::~set()
		{

		}
		long long set::sadd(const std::string& key, const std::list<std::string>& members)
		{
			std::list<std::string> commands{ "SADD",key };
			commands.insert(commands.end(), members.begin(), members.end());
			return cli_.sendListCommand(commands).asInteger();
		}
		long long set::scard(const std::string& key)
		{
			return cli_.sendSafeCommand("SCARD", key).asInteger();
		}

		redis::reply set::sdiff(const std::list<std::string>& keys)
		{
			std::list<std::string> commands{ "SDIFF"};
			commands.insert(commands.end(), keys.begin(), keys.end());
			return cli_.sendListCommand(commands);
		}

		long long set::sdiffstore(const std::string& destination, const std::list<std::string>& keys)
		{
			std::list<std::string> commands{ "SDIFFSTORE", destination };
			commands.insert(commands.end(), keys.begin(), keys.end());
			return cli_.sendListCommand(commands).asInteger();
		}
		reply set::sinter(const std::list<std::string>& keys)
		{
			std::list<std::string> commands{ "SINTER"};
			commands.insert(commands.end(), keys.begin(), keys.end());
			return cli_.sendListCommand(commands);
		}

		long long set::sinterstore(const std::string& destination, const std::list<std::string>& keys)
		{
			std::list<std::string> commands{ "SINTERSTORE", destination };
			commands.insert(commands.end(), keys.begin(), keys.end());
			return cli_.sendListCommand(commands).asInteger();
		}
		bool set::sismember(const std::string& key, const std::string& member)
		{
			return cli_.sendSafeCommand("SISMEMBER", key, member);
		}
		reply set::smembers(const std::string& key)
		{
			return cli_.sendSafeCommand("SMEMBERS", key);
		}
		bool set::smove(const std::string& source, const std::string& destination, const std::string& member)
		{
			return cli_.sendSafeCommand("SMOVE", source, destination, member);
		}
		std::string	set::spop(const std::string& key)
		{
			return cli_.sendSafeCommand("SPOP", key).asString();
		}
		reply set::srandmember(const std::string& key, size_t count /* = 0xffffffffffffffff */)
		{
			return cli_.sendSafeCommand("SRANDMEMBER", key, count);
		}

		long long set::srem(const std::string& key, const std::list<std::string>& members)
		{
			std::list<std::string> commands{ "SREM"};
			commands.insert(commands.end(), members.begin(),members.end());
			return cli_.sendListCommand(commands).asInteger();

		}
		reply set::sunion(const std::list<std::string>& keys)
		{
			std::list<std::string> commands{ "SUNION" };
			commands.insert(commands.end(), keys.begin(), keys.end());
			return cli_.sendListCommand(commands);
		}
		reply set::sunionstore(const std::string& destination, const std::list<std::string>& keys)
		{
			std::list<std::string> commands{ "SUNIONSTORE" };
			commands.insert(commands.end(), keys.begin(), keys.end());
			return cli_.sendListCommand(commands);
		}
		reply set::sscan(const std::string& key,int cursor, const std::string& matchPattern /* = "*" */, int count /* = 10 */)
		{
			return cli_.sendSafeCommand("SSCAN", key, cursor, "MATCH", matchPattern, "COUNT", count);
		}
	};
};