
#include "redis/client.hpp"

namespace redis {
	namespace op {

		string::string(client& cli)
			:cli_(cli)
		{

		}
		string::~string()
		{
		
		}
		long long string::append(const std::string& key, const std::string& appStr)
		{
			return cli_.sendSafeCommand("APPEND", key, appStr).asInteger();
		}
		long long string::bitcount(const std::string& key, int start /* = 0 */, int end /* = -1 */)
		{
			return cli_.sendSafeCommand("BITCOUNT", key, start,end).asInteger();
		}
		long long string::bitop(const std::string& subCmd, const std::string& destkey, const std::list<std::string>& keys)
		{
			std::list<std::string> cmds{ "BITOP" ,subCmd ,destkey };
			cmds.insert(cmds.end(), keys.begin(), keys.end());
			return cli_.sendListCommand(cmds).asInteger();
		}
		long long string::bitopAnd(const std::string& destkey, const std::list<std::string>& keys)
		{
			return bitop("AND", destkey, keys);
		}
		long long string::bitopOr(const std::string& destkey, const std::list<std::string>& keys)
		{
			return bitop("OR", destkey, keys);
		}
		long long string::bitopXor(const std::string& destkey, const std::list<std::string>& keys)
		{
			return bitop("XOR", destkey, keys);
		}
		long long string::bitopNot(const std::string& destkey,const std::string& key)
		{		
			return bitop("NOT", destkey, { key });
		}
		long long string::decr(const std::string& key)
		{
			return cli_.sendSafeCommand("DECR", key).asInteger();
		}
		long long string::decrby(const std::string& key, long long decrement)
		{
			return cli_.sendSafeCommand("DECRBY", key, decrement).asInteger();
		}
		std::string string::get(const std::string& key)
		{
			return cli_.sendSafeCommand("GET", key).asString();
		}
		long long string::getbit(const std::string& key, int offset)
		{
			return cli_.sendSafeCommand("GETBIT", key, offset).asInteger();
		}
		std::string string::getrange(const std::string& key, int start, int end)
		{
			return cli_.sendSafeCommand("GETRANGE", key, start, end).asString();
		}

		std::string string::getset(const std::string& key, const std::string& newvalue)
		{
			return cli_.sendSafeCommand("GETSET", key, newvalue).asString();
		}
		long long string::incr(const std::string& key)
		{
			return cli_.sendSafeCommand("INCR", key).asInteger();
		}
		long long string::incrby(const std::string& key, long long increment)
		{
			return cli_.sendSafeCommand("INCRBY", key, increment).asInteger();
		}
		std::string string::incrbyfloat(const std::string& key, double increment)
		{
			return cli_.sendSafeCommand("INCRBYFLOAT", key, increment).asString();
		}

		reply string::mget(const std::list<std::string>& keys)
		{
			std::list<std::string> commands{ "MGET" };
			commands.insert(commands.end(), keys.begin(), keys.end());
			return cli_.sendListCommand(commands);
		}
		void string::mset(const std::multimap<std::string, std::string>& keyValues)
		{
			std::list<std::string> commands{ "MSET" };

			for (const auto& kv : keyValues)
			{
				commands.push_back(kv.first);
				commands.push_back(kv.second);
			}
			cli_.sendListCommand(commands);
		}

		bool string::msetnx(const std::multimap<std::string, std::string>& keyValues)
		{
			std::list<std::string> commands{ "MSETNX" };

			for (const auto& kv : keyValues)
			{
				commands.push_back(kv.first);
				commands.push_back(kv.second);
			}
			return cli_.sendListCommand(commands);
		}
		void string::psetex(const std::string& key, time_t milliseconds, const std::string& value)
		{
			cli_.sendSafeCommand("PSETEX", key, milliseconds, value);
		}
		void string::set(const std::string& key, const std::string& value)
		{
			cli_.sendSafeCommand("SET", key, value);
		}
		long long string::setbit(const std::string& key, int offset, int bit)
		{
			return cli_.sendSafeCommand("SETBIT", key, offset,bit).asInteger();
		}
		void string::setex(const std::string& key, time_t seconds, const std::string& value) 
		{
			cli_.sendSafeCommand("SETEX", key, seconds, value);
		}
		bool string::setnx(const std::string& key, const std::string& value)
		{
			return cli_.sendSafeCommand("SETNX", key, value);
		}
		long long string::setrange(const std::string& key, int offset, const std::string& value)
		{
			return cli_.sendSafeCommand("SETRANGE", key, offset, value).asInteger();
		}
		long long string::strlen(const std::string& key) 
		{
			return cli_.sendSafeCommand("STRLEN", key).asInteger();
		}
	};
};