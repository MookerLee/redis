#include "redis/client.hpp"

namespace redis {
	namespace container {
		sortedset::sortedset(client& cli)
			:cli_(cli)
		{

		}
		sortedset::~sortedset()
		{

		}

		redis::reply sortedset::zadd(const std::string& key, 
			const std::multimap<long long,std::string>& scoreMembers)
		{
			std::list<std::string> commands{ "ZADD",key };

			for (const auto& sm : scoreMembers)
			{
				commands.push_back(std::to_string(sm.first));
				commands.push_back(sm.second);
			}

			return cli_.sendListCommand(commands);
		}
		redis::reply sortedset::zcard(const std::string& key)
		{
			return cli_.sendSafeCommand("ZCARD", key);
		}
		redis::reply sortedset::zcount(const std::string& key, 
			const std::string& min /*= "-inf"*/, 
			const std::string& max /*= "+inf"*/)
		{
			return cli_.sendSafeCommand("ZCOUNT", key, min, max);
		}
		redis::reply sortedset::zincrby(const std::string& key, 
			const std::string& increment, 
			const std::string& member)
		{
			return cli_.sendSafeCommand("ZINCRBY", key, increment, member);
		}
		redis::reply sortedset::zrange(const std::string& key, 
			int start, 
			int stop, 
			bool withscores /* = true */)
		{
			std::list<std::string> commands{ "ZINCRBY" ,std::to_string(start),std::to_string(stop) };
			if (withscores) commands.push_back("WITHSCORES");

			return cli_.sendListCommand(commands);
		}
		reply sortedset::zrangebyscore(const std::string& key,
			const std::string& min /* = "-inf" */,
			const std::string& max /* = "+inf" */,
			bool withscores /* = true */,
			const std::pair<int, int>& limit)
		{
			std::list<std::string> commands{ "ZRANGEBYSCORE", key, min, max };
			if (withscores) commands.push_back("WITHSCORES");
			
			commands.push_back("LIMIT");
			commands.push_back(std::to_string(limit.first));
			commands.push_back(std::to_string(limit.second));
					
			return cli_.sendListCommand(commands);
		}
		reply sortedset::zrank(const std::string& key, const std::string& member)
		{
			return cli_.sendSafeCommand("ZRANK", key, member);
		}
		redis::reply sortedset::zrem(const std::string& key, 
			const std::list<std::string>& members)
		{
			std::list<std::string> commands{ "ZREM",key };
			commands.insert(commands.end(), members.begin(), members.end());

			return cli_.sendListCommand(commands);
		}
		redis::reply sortedset::zremrangebyrank(const std::string& key, 
			int start /*= 0*/, 
			int stop /*= -1*/)
		{
			return cli_.sendSafeCommand("ZREMRANGEBYRANK", key, start, stop);
		}
		redis::reply sortedset::zremrangebyscore(const std::string& key, 
			const std::string& min /*= "-inf"*/, 
			const std::string& max /*= "+inf"*/)
		{
			return cli_.sendSafeCommand("ZREMRANGEBYSCORE", key, min, max);
		}
		redis::reply sortedset::zrevrange(const std::string& key, 
			int start /*= 0*/, 
			int stop /*= -1*/, 
			bool withscores /*= true*/)
		{
			std::list<std::string> commands{ "ZREVRANGE" ,std::to_string(start),std::to_string(stop) };

			if(withscores) commands.push_back("WITHSCORES");
			return cli_.sendListCommand(commands);
		}
		reply sortedset::zrevrangebyscore(const std::string& key, 
			const std::string& max /* = "+inf" */, 
			const std::string& min /* = "-inf" */, 
			bool withscores,
			const std::pair<int, int>& limit)
		{
			std::list<std::string> commands{ "ZREVRANGEBYSCORE" ,key,max,min };

			if (withscores) commands.push_back("WITHSCORES");

			commands.push_back("LIMIT");
			commands.push_back(std::to_string(limit.first));
			commands.push_back(std::to_string(limit.second));

			return cli_.sendListCommand(commands);
		}
		reply sortedset::zrevrank(const std::string& key, const std::string& member)
		{
			return cli_.sendSafeCommand("ZREVRANK", key, member);
		}
		redis::reply sortedset::zscore(const std::string& key, const std::string& member)
		{
			return cli_.sendSafeCommand("ZSCORE", key, member);
		}

		reply sortedset::zunionstore(const std::string& destination,
			const std::list<std::string>& keys,
			const std::list<std::string>& weights /* =  */,
			const std::string& aggregate /* = "" */)
		{
			std::list<std::string> commands{"ZUNIONSTORE",destination ,std::to_string(keys.size())};
			commands.insert(commands.end(), keys.begin(), keys.end());

			if (!weights.empty())
			{
				commands.push_back("WEIGHTS");
				commands.insert(commands.end(), weights.begin(), weights.end());
			}
			if (!aggregate.empty())
			{
				commands.push_back("AGGREGATE");
				commands.push_back(aggregate);
			}
			return cli_.sendListCommand(commands);
		}
		reply sortedset::zinterstore(const std::string& destination,
			const std::list<std::string>& keys,
			const std::list<std::string>& weights /* =  */,
			const std::string& aggregate /* = "" */)
		{
			std::list<std::string> commands{ "ZINTERSTORE",destination ,std::to_string(keys.size()) };
			commands.insert(commands.end(), keys.begin(), keys.end());

			if (!weights.empty())
			{
				commands.push_back("WEIGHTS");
				commands.insert(commands.end(), weights.begin(), weights.end());
			}
			if (!aggregate.empty())
			{
				commands.push_back("AGGREGATE");
				commands.push_back(aggregate);
			}
			return cli_.sendListCommand(commands);
		}

		reply sortedset::zscan(const std::string& key, 
			int cursor /* = 0 */, 
			const std::string& matchPattern /* = "*" */, 
			int count /* = 10 */)
		{
			return cli_.sendSafeCommand("ZSCAN", key, cursor, matchPattern, count);
		}
		reply sortedset::zrangebylex(const std::string& key,
			const std::string& min /* = "-inf" */,
			const std::string& max /* = "+inf" */,
			const std::pair<int, int>& limit )
		{
			std::list<std::string> commands{ "ZRANGEBYLEX",key,min,max };
			
			commands.push_back("LIMIT");
			commands.push_back(std::to_string(limit.first));
			commands.push_back(std::to_string(limit.second));
			
			return cli_.sendListCommand(commands);
		}
		redis::reply sortedset::zlexcount(const std::string& key, 
			const std::string& min /*= "-inf"*/, 
			const std::string& max /*= "+inf"*/)
		{
			return cli_.sendSafeCommand("ZLEXCOUN", key, min, max);
		}
		redis::reply sortedset::zremrangebylex(const std::string& key, 
			const std::string& min /*= "-inf"*/, 
			const std::string& max /*= "+inf"*/)
		{
			return cli_.sendSafeCommand("ZREMRANGEBYLEX", key, min, max);
		}
	};
};