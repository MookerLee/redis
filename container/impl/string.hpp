
#include "redis/client.hpp"

namespace redis {
	namespace container {

		string::string(client& cli)
			:cli_(cli)
		{

		}
		string::~string()
		{
		
		}
		reply string::append(const std::string& key, const std::string& str)
		{
			return cli_.sendSafeCommand("APPEND", key, str);
		}
		reply string::bitcount(const std::string& key, int start /* = 0 */, int end /* = -1 */)
		{
			return cli_.sendSafeCommand("BITCOUNT", key, start,end);
		}
		reply string::bitop(const std::string& operation, const std::string& destkey, const std::list<std::string>& keys)
		{
			std::list<std::string> commands{ "BITOP" ,operation ,destkey };
			commands.insert(commands.end(), keys.begin(), keys.end());
			return cli_.sendListCommand(commands);
		}
		reply string::bitopAnd(const std::string& destkey, const std::list<std::string>& keys)
		{
			return bitop("AND", destkey, keys);
		}
		reply string::bitopOr(const std::string& destkey, const std::list<std::string>& keys)
		{
			return bitop("OR", destkey, keys);
		}
		reply string::bitopXor(const std::string& destkey, const std::list<std::string>& keys)
		{
			return bitop("XOR", destkey, keys);
		}
		reply string::bitopNot(const std::string& destkey,const std::string& key)
		{		
			return bitop("NOT", destkey, { key });
		}
		reply string::decr(const std::string& key)
		{
			return cli_.sendSafeCommand("DECR", key);
		}
		reply string::decrby(const std::string& key, long long decrement)
		{
			return cli_.sendSafeCommand("DECRBY", key, decrement);
		}
		reply string::get(const std::string& key)
		{
			return cli_.sendSafeCommand("GET", key);
		}
		reply string::getbit(const std::string& key, int offset)
		{
			return cli_.sendSafeCommand("GETBIT", key, offset);
		}
		reply string::getrange(const std::string& key, int start /*= 0*/, int end /*= -1*/)
		{
			return cli_.sendSafeCommand("GETRANGE", key, start, end);
		}
		reply string::getset(const std::string& key, const std::string& value)
		{
			return cli_.sendSafeCommand("GETSET", key, value);
		}
		reply string::incr(const std::string& key)
		{
			return cli_.sendSafeCommand("INCR", key);
		}
		reply string::incrby(const std::string& key, long long increment)
		{
			return cli_.sendSafeCommand("INCRBY", key, increment);
		}
		reply string::incrbyfloat(const std::string& key, const std::string& increment)
		{
			return cli_.sendSafeCommand("INCRBYFLOAT", key, increment);
		}

		reply string::mget(const std::list<std::string>& keys)
		{
			std::list<std::string> commands{ "MGET" };
			commands.insert(commands.end(), keys.begin(), keys.end());
			return cli_.sendListCommand(commands);
		}
		reply string::mset(const std::multimap<std::string,std::string>& keyValues)
		{
			std::list<std::string> commands{ "MSET" };

			for (const auto& kv : keyValues)
			{
				commands.push_back(kv.first);
				commands.push_back(kv.second);
			}
			return cli_.sendListCommand(commands);
		}

		reply string::msetnx(const std::multimap<std::string, std::string>& keyValues)
		{
			std::list<std::string> commands{ "MSETNX" };

			for (const auto& kv : keyValues)
			{
				commands.push_back(kv.first);
				commands.push_back(kv.second);
			}
			return cli_.sendListCommand(commands);
		}
		reply string::psetex(const std::string& key, time_t milliseconds, const std::string& value)
		{
			return cli_.sendSafeCommand("PSETEX", key, milliseconds, value);
		}
		reply string::set(const std::string& key, const std::string& value)
		{
			return cli_.sendSafeCommand("SET", key, value);
		}
		reply string::setbit(const std::string& key, int offset, int value)
		{
			return cli_.sendSafeCommand("SETBIT", key, offset,value);
		}
		reply string::setex(const std::string& key, time_t seconds, const std::string& value) 
		{
			return cli_.sendSafeCommand("SETEX", key, seconds, value);
		}
		reply string::setnx(const std::string& key, const std::string& value)
		{
			return cli_.sendSafeCommand("SETNX", key, value);
		}
		reply string::setrange(const std::string& key, int offset, const std::string& value)
		{
			return cli_.sendSafeCommand("SETRANGE", key, offset, value);
		}
		reply string::strlen(const std::string& key) 
		{
			return cli_.sendSafeCommand("STRLEN", key);
		}
	};
};