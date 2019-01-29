#include "redis/client.hpp"

namespace redis {
	namespace op {
		hash::hash(client& cli)
			:cli_(cli)
		{

		}
		hash::~hash()
		{

		}
		long long hash::hdel(const std::string& key, const std::list<std::string>&  fields)
		{
			std::list<std::string> commands{ "HDEL", key };
			commands.insert(commands.end(), fields.begin(), fields.end());
			return cli_.sendListCommand(commands);
		}
		bool hash::hexist(const std::string& key, const std::string& field)
		{
			return cli_.sendSafeCommand("HEXIST", key, field);
		}
		std::string hash::hget(const std::string& key, const std::string& field)
		{
			return cli_.sendSafeCommand("HGET", key, field);
		}
		reply hash::hgetall(const std::string& key)
		{
			return cli_.sendSafeCommand("HGETALL", key);
		}
		long long hash::hincrby(const std::string& key, const std::string& field, long long increment)
		{
			return cli_.sendSafeCommand("HINCRBY", key, field, increment);
		}
		std::string hash::hincrbyfloat(const std::string& key, const std::string& field, double increment)
		{
			return cli_.sendSafeCommand("HINCRBYFLOAT", key, field, increment);
		}
		reply hash::hkeys(const std::string& key)
		{
			return cli_.sendSafeCommand("HKEYS", key);
		}
		long long hash::hlen(const std::string& key)
		{
			return cli_.sendSafeCommand("HLEN", key);
		}
		reply hash::hmget(const std::string& key, const std::list<std::string>&  fields)
		{
			std::list<std::string> commands{ "HMGET", key };
			commands.insert(commands.end(), fields.begin(), fields.end());
			return cli_.sendListCommand(commands);
		}
		reply hash::hmset(const std::string& key, const std::multimap<std::string,std::string>& fieldValues)
		{
			std::list<std::string> commands{ "HMSET", key };

			for (const auto& fv : fieldValues)
			{
				commands.push_back(fv.first);
				commands.push_back(fv.second);
			}
			return cli_.sendListCommand(commands);
		}
		long long hash::hset(const std::string& key, const std::string& field, const std::string& value)
		{
			return cli_.sendSafeCommand("HSET", key, field, value);
		}
		bool hash::hsetnx(const std::string& key, const std::string& field, const std::string& value)
		{
			return cli_.sendSafeCommand("HSETNX", key, field, value);
		}
		reply hash::hvals(const std::string& key)
		{
			return cli_.sendSafeCommand("HVALS", key);
		}
		reply hash::hscan(const std::string& key,int cursor, const std::string& matchPattern /* = "*" */, int count /* = 10 */)
		{
			return cli_.sendSafeCommand("HSCAN", key, cursor, "MATCH", matchPattern, "COUNT", count);
		}
		long long hash::hstrlen(const std::string& key, const std::string& field)
		{
			return cli_.sendSafeCommand("HSTRLEN", key, field);
		}
	}
};