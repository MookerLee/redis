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
		redis::reply list::blpop(const std::list<std::string>& keys, time_t timeout /*= 0*/)
		{
			std::list<std::string> commands{ "BLPOP" };
			commands.insert(commands.end(), keys.begin(), keys.end());
			commands.push_back(std::to_string(timeout));

			return cli_.sendListCommand(commands);
		}
		redis::reply list::brpop(const std::list<std::string>& keys, time_t timeout/*= 0*/)
		{
			std::list<std::string> commands{ "BRPOP" };
			commands.insert(commands.end(), keys.begin(), keys.end());
			commands.push_back(std::to_string(timeout));
			return cli_.sendListCommand(commands);
		}

		reply list::brpoplpush(const std::string& source, const std::string& destination, time_t timeout)
		{
			return cli_.sendSafeCommand("BRPOPLPUSH", source, destination, timeout);
		}
		redis::reply list::lindex(const std::string& key, size_t idx)
		{
			return cli_.sendSafeCommand("LINDEX", key, idx);
		}
		redis::reply list::linsertBefore(const std::string& key, const std::string& pivot, const std::string& value)
		{
			return linsert(key, "BEFORE", pivot, value);
		}
		reply list::linsert(const std::string& key,
			const std::string& subcommand,
			const std::string& pivot,
			const std::string& value)
		{
			return cli_.sendSafeCommand("LINSERT", key, subcommand, pivot, value);
		}
		redis::reply list::linsertAfter(const std::string& key, const std::string& pivot, const std::string& value)
		{
			return linsert(key, "AFTER", pivot, value);
		}
		redis::reply list::llen(const std::string& key)
		{
			return cli_.sendSafeCommand("LLEN", key);
		}
		redis::reply list::lpop(const std::string& key)
		{
			return cli_.sendSafeCommand("LPOP", key);
		}

		redis::reply list::lpush(const std::string& key, const std::list<std::string>& values)
		{
			std::list<std::string> commands{ "LPUSH" ,key};
			commands.insert(commands.end(), values.begin(), values.end());
			return cli_.sendListCommand(commands);
		}
		redis::reply list::lpushx(const std::string& key, const std::list<std::string>& values)
		{
			std::list<std::string> commands{ "LPUSHX" ,key };
			commands.insert(commands.end(), values.begin(), values.end());
			return cli_.sendListCommand(commands);
		}
		redis::reply list::lrange(const std::string& key, int start /*= 0*/, int stop /*= -1*/)
		{
			return cli_.sendSafeCommand("LRANGE", key, start,stop);
		}
		redis::reply list::lrem(const std::string& key, size_t count, const std::string& value)
		{
			return cli_.sendSafeCommand("LREM", key, count, value);
		}
		redis::reply list::lset(const std::string& key, size_t index, const std::string& value)
		{
			return cli_.sendSafeCommand("LSET", key, index, value);
		}
		redis::reply list::ltrim(const std::string& key, int start /*= 0*/, int stop /*= -1*/)
		{
			return cli_.sendSafeCommand("LTRIM", key, start, stop);
		}
		redis::reply list::rpop(const std::string& key)
		{
			return cli_.sendSafeCommand("RPOP", key);
		}
		redis::reply list::rpoplpush(const std::string& source, const std::string& destination)
		{
			return cli_.sendSafeCommand("RPOPLPUSH", source, destination);
		}
		redis::reply list::rpush(const std::string& key, const std::list<std::string>& values)
		{
			std::list<std::string> commands{ "RPUSH" ,key };
			commands.insert(commands.end(), values.begin(), values.end());
			return cli_.sendListCommand(commands);
		}
		redis::reply list::rpushx(const std::string& key, const std::string& value)
		{
			return cli_.sendSafeCommand("RPUSHX", key, value);
		}
	}
};