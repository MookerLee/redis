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
		template <class...Args>
		long long hash::del(const std::string& key, Args... fields)
		{
			return cli_.sendSafeCommand("HDEL", key, fields...).asInteger();
		}
		bool hash::exist(const std::string& key, const std::string& field)
		{
			return cli_.sendSafeCommand("HEXIST", key, field);
		}
		std::string hash::get(const std::string& key, const std::string& field)
		{
			return cli_.sendSafeCommand("HGET", key, field);
		}
		reply hash::getAll(const std::string& key)
		{
			return cli_.sendSafeCommand("HGETALL", key);
		}
		long long hash::incrBy(const std::string& key, const std::string& field, long long increment)
		{
			return cli_.sendSafeCommand("HINCRBY", key, field, increment);
		}
		std::string hash::incrByFloat(const std::string& key, const std::string& field, double increment)
		{
			return cli_.sendSafeCommand("HINCRBYFLOAT", key, field, increment);
		}
		reply hash::keys(const std::string& key)
		{
			return cli_.sendSafeCommand("HKEYS", key);
		}
		long long hash::len(const std::string& key)
		{
			return cli_.sendSafeCommand("HLEN", key);
		}
		template<class... Args>
		reply hash::mget(const std::string& key, Args... fields)
		{
			return cli_.sendSafeCommand("HMGET", key,fields...);
		}
		template <class... Args>
		reply hash::mset(const std::string& key, std::initializer_list<Args>... pairs)
		{
			return cli_.sendPairsCommand( "HMSET", key, pairs...);
		}
		long long hash::set(const std::string& key, const std::string& field, const std::string& value)
		{
			return cli_.sendSafeCommand("HSET", key, field, value).asInteger();
		}
		bool hash::setNx(const std::string& key, const std::string& field, const std::string& value)
		{
			return cli_.sendSafeCommand("HSETNX", key, field, value);
		}
		reply hash::vals(const std::string& key)
		{
			return cli_.sendSafeCommand("HSETNX", key);
		}
		reply hash::scan(const std::string& key,int cursor, const std::string& matchPattern /* = "*" */, int count /* = 10 */)
		{
			return cli_.sendSafeCommand("HSCAN", key, cursor, "MATCH", matchPattern, "COUNT", count);
		}
		long long hash::strLen(const std::string& key, const std::string& field)
		{
			return cli_.sendSafeCommand("HSTRLEN", key, field);
		}
	}
};