
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
		long long string::bitCount(const std::string& key, int start /* = 0 */, int end /* = -1 */)
		{
			return cli_.sendSafeCommand("BITCOUNT", key, start,end).asInteger();
		}
		template  <class... Args>
		long long string::bitOP(const std::string& subCmd, const std::string& destkey, Args... keys)
		{
			return cli_.sendSafeCommand("BITOP", subCmd, destkey, keys...).asInteger();
		}
		template <class... Args>
		long long string::bitOPAnd(const std::string& destkey, Args... keys)
		{
			return bitOP("AND", destkey, keys...);
		}

		template <class... Args>
		long long string::bitOPOr(const std::string& destkey, Args... keys)
		{
			return bitOP("OR", destkey, keys...);
		}
		template <class... Args>
		long long string::bitOPXor(const std::string& destkey, Args... keys)
		{
			return bitOP("XOR", destkey, keys...);
		}
		long long string::bitOPNot(const std::string& destkey,const std::string& key)
		{		
			return bitOP("NOT", destkey, key);	
		}
		long long string::decr(const std::string& key)
		{
			return cli_.sendSafeCommand("DECR", key).asInteger();
		}
		long long string::decrBy(const std::string& key, long long decrement)
		{
			return cli_.sendSafeCommand("DECRBY", key, decrement).asInteger();
		}
		std::string string::get(const std::string& key)
		{
			return cli_.sendSafeCommand("GET", key).asString();
		}
		long long string::getBit(const std::string& key, int offset)
		{
			return cli_.sendSafeCommand("GETBIT", key, offset).asInteger();
		}
		std::string string::getRange(const std::string& key, int start, int end)
		{
			return cli_.sendSafeCommand("GETRANGE", key, start, end).asString();
		}

		std::string string::getSet(const std::string& key, const std::string& newvalue)
		{
			return cli_.sendSafeCommand("GETSET", key, newvalue).asString();
		}
		long long string::incr(const std::string& key)
		{
			return cli_.sendSafeCommand("INCR", key).asInteger();
		}
		long long string::incrBy(const std::string& key, long long increment)
		{
			return cli_.sendSafeCommand("INCRBY", key, increment).asInteger();
		}
		std::string string::incrByFloat(const std::string& key, double increment)
		{
			return cli_.sendSafeCommand("INCRBYFLOAT", key, increment).asString();
		}
		template <class... Args>
		reply string::mget(Args... keys)
		{
			return cli_.sendSafeCommand("MGET", keys...);
		}
		template <class... Args>
		void string::mset(std::initializer_list<Args>... pairs)
		{
			cli_.sendPairsCommand("MSET", pairs...);
		}
		template <class... Args>
		bool string::msetNx(std::initializer_list<Args>... pairs)
		{
			return cli_.sendPairsCommand("MSETNX", pairs...);
		}
		void string::psetEx(const std::string& key, time_t milliseconds, const std::string& value)
		{
			cli_.sendSafeCommand("PSETEX", key, milliseconds, value);
		}
		void string::set(const std::string& key, const std::string& value)
		{
			cli_.sendSafeCommand("SET", key, value);
		}
		long long string::setBit(const std::string& key, int offset, int bit)
		{
			return cli_.sendSafeCommand("SETBIT", key, offset,bit).asInteger();
		}
		void string::setEx(const std::string& key, time_t seconds, const std::string& value) 
		{
			cli_.sendSafeCommand("SETEX", key, seconds, value);
		}
		bool string::setNx(const std::string& key, const std::string& value)
		{
			return cli_.sendSafeCommand("SETNX", key, value);
		}
		long long string::setRange(const std::string& key, int offset, const std::string& value)
		{
			return cli_.sendSafeCommand("SETRANGE", key, offset, value).asInteger();
		}
		long long string::strLen(const std::string& key) 
		{
			return cli_.sendSafeCommand("STRLEN", key).asInteger();
		}
	};
};