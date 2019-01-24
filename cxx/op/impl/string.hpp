
#include "redis/cxx/impl/format.hpp"
#include "redis/cxx/client.hpp"

namespace CXXRedis {
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
			return cli_.send(format::formatCmd("APPEND", key, appStr)).asInteger();
		}
		long long string::bitCount(const std::string& key, int start /* = 0 */, int end /* = -1 */)
		{
			return cli_.send(format::formatCmd("BITCOUNT", key, start,end)).asInteger();
		}
		template  <class... Args>
		long long string::bitOP(const std::string& subCmd, const std::string& destkey, Args... keys)
		{
			return cli_.send(format::formatCmd("BITOP", subCmd, destkey, keys...)).asInteger();
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
			return cli_.send(format::formatCmd("DECR", key)).asInteger();
		}
		long long string::decrBy(const std::string& key, long long decrement)
		{
			return cli_.send(format::formatCmd("DECRBY", key, decrement)).asInteger();
		}
		std::string string::get(const std::string& key)
		{
			return cli_.send(format::formatCmd("GET", key)).asString();
		}
		long long string::getBit(const std::string& key, int offset)
		{
			return cli_.send(format::formatCmd("GETBIT", key, offset)).asInteger();
		}
		std::string string::getRange(const std::string& key, int start, int end)
		{
			return cli_.send(format::formatCmd("GETRANGE", key, start,end)).asString();
		}

		std::string string::getSet(const std::string& key, const std::string& newvalue)
		{
			return cli_.send(format::formatCmd("GETSET", key, newvalue)).asString();
		}
		long long string::incr(const std::string& key)
		{
			return cli_.send(format::formatCmd("INCR", key)).asInteger();
		}
		long long string::incrBy(const std::string& key, long long increment)
		{
			return cli_.send(format::formatCmd("INCRBY", key, increment)).asInteger();
		}
		std::string string::incrByFloat(const std::string& key, double increment)
		{
			return cli_.send(format::formatCmd("INCRBYFLOAT", key, increment)).asString();
		}
		template <class... Args>
		response string::mget(Args... keys)
		{
			return cli_.send(format::formatCmd("MGET", keys...));
		}
		template <class... Args>
		void string::mset(std::initializer_list<Args>... pairs)
		{
			cli_.send(format::formatPairs("MSET", pairs...));
		}
		template <class... Args>
		bool string::msetNx(std::initializer_list<Args>... pairs)
		{
			return cli_.send(format::formatPairs("MSETNX", pairs...));
		}
		void string::psetEx(const std::string& key, time_t milliseconds, const std::string& value)
		{
			cli_.send(format::formatCmd("PSETEX", key, milliseconds, value));
		}
		void string::set(const std::string& key, const std::string& value)
		{
			cli_.send(format::formatCmd("SET", key, value));
		}
		long long string::setBit(const std::string& key, int offset, int bit)
		{
			return cli_.send(format::formatCmd("SETBIT", key, offset,bit)).asInteger();
		}
		void string::setEx(const std::string& key, time_t seconds, const std::string& value) 
		{
			cli_.send(format::formatCmd("SETEX", key, seconds, value));
		}
		bool string::setNx(const std::string& key, const std::string& value)
		{
			return cli_.send(format::formatCmd("SETNX", key, value));
		}
		long long string::setRange(const std::string& key, int offset, const std::string& value)
		{
			return cli_.send(format::formatCmd("SETRANGE", key, offset, value)).asInteger();
		}
		long long string::strLen(const std::string& key) 
		{
			return cli_.send(format::formatCmd("STRLEN", key)).asInteger();
		}
	};
};