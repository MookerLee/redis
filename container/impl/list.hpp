#include "redis/client.hpp"
namespace redis {
	namespace container {
		list::list(client& cli)
			:cli_(cli)
		{

		}
		list::~list()
		{
			
		}
		reply list::blpop(const std::list<std::string>& keys)
		{
			std::list<std::string> commands{ "BLPOP" };
			commands.insert(commands.end(), keys.begin(), keys.end());
			return cli_.sendListCommand(commands);
		}
		reply list::brpop(const std::list<std::string>& keys)
		{
			std::list<std::string> commands{ "BRPOP" };
			commands.insert(commands.end(), keys.begin(), keys.end());
			return cli_.sendListCommand(commands);
		}

		reply list::brpoplpush(const std::string& source, const std::string& destination, time_t timeout)
		{
			return cli_.sendSafeCommand("BRPOPLPUSH", source, destination, timeout);
		}
		std::string list::lindex(const std::string& key, size_t idx)
		{
			return cli_.sendSafeCommand("LINDEX", key, idx).asString();
		}
		long long list::linsertBefore(const std::string& key, const std::string& pivot, const std::string& value)
		{
			return cli_.sendSafeCommand("LINSERT", key, "BEFORE", pivot, value);
		}
		long long list::linsertAfter(const std::string& key, const std::string& pivot, const std::string& value)
		{
			return cli_.sendSafeCommand("LINSERT", key, "AFTER", pivot, value);
		}
		long long list::llen(const std::string& key)
		{
			return cli_.sendSafeCommand("LLEN", key);
		}
		std::string list::lpop(const std::string& key)
		{
			return cli_.sendSafeCommand("LPOP", key);
		}

		long long list::lpush(const std::string& key, const std::list<std::string>& values)
		{
			std::list<std::string> commands{ "LPUSH" ,key};
			commands.insert(commands.end(), values.begin(), values.end());
			return cli_.sendListCommand(commands);
		}
		long long list::lpushx(const std::string& key, const std::list<std::string>& values)
		{
			std::list<std::string> commands{ "LPUSHX" ,key };
			commands.insert(commands.end(), values.begin(), values.end());
			return cli_.sendListCommand(commands);
		}
		reply list::lrange(const std::string& key, size_t start /* = 0 */, size_t stop /* = -1 */)
		{
			return cli_.sendSafeCommand("LRANGE", key, start,stop);
		}
		long long list::lrem(const std::string& key, size_t count, const std::string& value)
		{
			return cli_.sendSafeCommand("LREM", key, count, value);
		}
		void list::lset(const std::string& key, size_t index, const std::string& value)
		{
			cli_.sendSafeCommand("LSET", key, index, value);
		}
		void list::ltrim(const std::string& key, size_t start /* = 0 */, size_t stop /* = -1 */)
		{
			cli_.sendSafeCommand("LTRIM", key, start, stop);
		}
		std::string list::rpop(const std::string& key)
		{
			return cli_.sendSafeCommand("RPOP", key);
		}
		std::string list::rpoplpush(const std::string& source, const std::string& destination)
		{
			return cli_.sendSafeCommand("RPOPLPUSH", source, destination);
		}
		long long list::rpush(const std::string& key, const std::list<std::string>& values)
		{
			std::list<std::string> commands{ "RPUSH" ,key };
			commands.insert(commands.end(), values.begin(), values.end());
			return cli_.sendListCommand(commands);
		}
		long long list::rpushx(const std::string& key, const std::string& value)
		{
			return cli_.sendSafeCommand("RPUSHX", key, value);
		}
	}
};