#include "redis/client.hpp"

namespace redis {
	namespace op {
		srotedSet::srotedSet(client& cli)
			:cli_(cli)
		{

		}
		srotedSet::~srotedSet()
		{

		}

		long long srotedSet::zadd(const std::string& key, 
			const std::multimap<long long, std::string>& scoreMembers)
		{
			std::list<std::string> cmds{ "ZADD",key };

			for (const auto& sm : scoreMembers)
			{
				cmds.push_back(std::to_string(sm.first));
				cmds.push_back(sm.second);
			}

			return cli_.sendListCommand(cmds).asInteger();
		}
		long long srotedSet::zcard(const std::string& key)
		{
			return cli_.sendSafeCommand("ZCARD", key);
		}
		long long srotedSet::zcount(const std::string& key, 
			const std::string& min, 
			const std::string& max)
		{
			return cli_.sendSafeCommand("ZCOUNT", key, min, max);
		}
		std::string srotedSet::zincrby(const std::string& key, 
			const std::string& increment, 
			const std::string& member)
		{
			return cli_.sendSafeCommand("ZINCRBY", key, increment, member);
		}
		redis::reply srotedSet::zrange(const std::string& key, 
			int start, 
			int stop, 
			bool withScores /* = true */)
		{
			std::list<std::string> commands{ "ZINCRBY" ,std::to_string(start),std::to_string(stop) };
			if (withScores) commands.push_back("WITHSCORES");

			return cli_.sendListCommand(commands);
		}
		reply srotedSet::zrangebyscore(const std::string& key,
			const std::string& min /* = "-inf" */,
			const std::string& max /* = "+inf" */,
			bool withScores /* = true */,
			const std::string& limit/* = ""*/)
		{
			std::list<std::string> commands{ "ZRANGEBYSCORE", key, min, max };
			if (withScores) commands.push_back("WITHSCORES");
			if (!limit.empty())
			{
				commands.push_back("LIMIT");
				commands.push_back(limit);
			}		
			return cli_.sendListCommand(commands);
		}
		reply srotedSet::zrank(const std::string& key, const std::string& member)
		{
			return cli_.sendSafeCommand("ZRANK", key, member);
		}
		long long srotedSet::zrem(const std::string& key, 
			const std::list<std::string>& members)
		{
			std::list<std::string> commands{ "ZREM",key };
			commands.insert(commands.end(), members.begin(), members.end());

			return cli_.sendListCommand(commands);
		}
		long long srotedSet::zremrangebyrank(const std::string& key, 
			int start /*= 0*/, 
			int stop /*= -1*/)
		{
			return cli_.sendSafeCommand("ZREMRANGEBYRANK", key, start, stop);
		}
		long long srotedSet::zremrangebyscore(const std::string& key, 
			const std::string& min /* = "-inf" */, 
			const std::string& max /* = "+inf" */)
		{
			return cli_.sendSafeCommand("ZREMRANGEBYSCORE", key, min, max);
		}
		redis::reply srotedSet::zrevrange(const std::string& key, 
			int start /*= 0*/, 
			int stop /*= -1*/, 
			bool withScores /*= true*/)
		{
			std::list<std::string> commands{ "ZREVRANGE" ,std::to_string(start),std::to_string(stop) };

			if(withScores) commands.push_back("WITHSCORES");
			return cli_.sendListCommand(commands);
		}
		reply srotedSet::zrevrangebyscore(const std::string& key, 
			const std::string& max /* = "+inf" */, 
			const std::string& min /* = "-inf" */, 
			bool withScores /* = true */,
			const std::string& limit)
		{
			std::list<std::string> commands{ "ZREVRANGEBYSCORE" ,key,max,min };

			if (withScores) commands.push_back("WITHSCORES");
			if (!limit.empty())
			{
				commands.push_back("LIMIT");
				commands.push_back(limit);
			}
			return cli_.sendListCommand(commands);
		}
		reply srotedSet::zrevrank(const std::string& key, const std::string& member)
		{
			return cli_.sendSafeCommand("ZREVRANK", key, member);
		}
		std::string srotedSet::zscore(const std::string& key, const std::string& member)
		{
			return cli_.sendSafeCommand("ZSCORE", key, member);
		}

		long long srotedSet::zunionstore(const std::string& destination,
			long long numkeys,
			const std::list<std::string>& keys,
			const std::list<std::string>& weights /* =  */,
			const std::string& aggregate /* = "" */)
		{
			std::list<std::string> commands{"ZUNIONSTORE",destination ,std::to_string(numkeys)};
			commands.insert(commands.end(), keys.begin(), keys.end());

			if (!weights.empty())
			{
				commands.push_back("WEIGHTS");
				commands.insert(commands.end(), weights.begin(), weights.end());
			}
			if (!aggregate.empty())
			{
				commands.push_back(aggregate);
			}
			return cli_.sendListCommand(commands);
		}
		long long srotedSet::zinterstore(const std::string& destination,
			long long numkeys,
			const std::list<std::string>& keys,
			const std::list<std::string>& weights /* =  */,
			const std::string& aggregate /* = "" */)
		{
			std::list<std::string> commands{ "ZINTERSTORE",destination ,std::to_string(numkeys) };
			commands.insert(commands.end(), keys.begin(), keys.end());

			if (!weights.empty())
			{
				commands.push_back("WEIGHTS");
				commands.insert(commands.end(), weights.begin(), weights.end());
			}
			if (!aggregate.empty())
			{
				commands.push_back(aggregate);
			}
			return cli_.sendListCommand(commands);
		}

		reply srotedSet::zscan(const std::string& key, 
			int cursor /* = 0 */, 
			const std::string& matchPattern /* = "*" */, 
			int count /* = 10 */)
		{
			return cli_.sendSafeCommand("ZSCAN", key, cursor, matchPattern, count);
		}
		reply srotedSet::zrangebylex(const std::string& key,
			const std::string& min /* = "-inf" */,
			const std::string& max /* = "+inf" */,
			const std::string& limit /* = "" */)
		{
			std::list<std::string> commands{ "ZRANGEBYLEX",key,min,max };
			if (!limit.empty())
			{
				commands.push_back("LIMIT");
				commands.push_back(limit);
			}
			return cli_.sendListCommand(commands);
		}
		long long srotedSet::zlexcount(const std::string& key, 
			const std::string& min /* = "-inf" */, 
			const std::string& max /* = "+inf" */)
		{
			return cli_.sendSafeCommand("ZLEXCOUN", key, min, max);
		}
		long long srotedSet::zremrangebylex(const std::string& key, 
			const std::string& min /* = "-inf" */, 
			const std::string& max /* = "+inf" */)
		{
			return cli_.sendSafeCommand("ZREMRANGEBYLEX", key, min, max);
		}
	};
};