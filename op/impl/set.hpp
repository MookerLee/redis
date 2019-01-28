
#include "redis/client.hpp"

namespace redis{
	namespace op {
		set::set(client& cli)
			:cli_(cli)
		{

		}
		set::~set()
		{

		}
		template<class... Args>
		long long set::add(const std::string& key, Args... members)
		{
			return cli_.sendSafeCommand("SADD", key, members...).asInteger();
		}
		long long set::card(const std::string& key)
		{
			return cli_.sendSafeCommand("SCARD", key).asInteger();
		}

		template<class... Args>
		reply set::diff(Args... keys)
		{
			return cli_.sendSafeCommand("SDIFF", keys...);
		}

		template<class... Args>
		long long set::diffStore(const std::string& destination, Args... keys)
		{
			return cli_.sendSafeCommand("SDIFFSTORE", destination,keys...).asInteger();
		}
		template<class... Args>
		reply set::inter(Args... keys)
		{
			return cli_.sendSafeCommand("SINTER", keys...);
		}

		template<class... Args>
		long long set::interStore(const std::string& destination, Args... keys)
		{
			return cli_.sendSafeCommand("SINTERSTORE", destination, keys...).asInteger();
		}
		bool set::isMember(const std::string& key, const std::string& member)
		{
			return cli_.sendSafeCommand("SISMEMBER", key, member);
		}
		reply set::members(const std::string& key)
		{
			return cli_.sendSafeCommand("SMEMBERS", key);
		}
		bool set::move(const std::string& source, const std::string& destination, const std::string& member)
		{
			return cli_.sendSafeCommand("SMOVE", source, destination, member);
		}
		std::string	set::pop(const std::string& key)
		{
			return cli_.sendSafeCommand("SPOP", key).asString();
		}
		reply set::randMember(const std::string& key, size_t count /* = 0xffffffffffffffff */)
		{
			return cli_.sendSafeCommand("SRANDMEMBER", key, count);
		}

		template<class... Args>
		long long set::remove(const std::string& key, Args... members)
		{
			return cli_.sendSafeCommand("SREM", key, members...);
		}
		template<class... Args>
		reply set::sunion(Args... keys)
		{
			return cli_.sendSafeCommand("SUNION ", keys...);
		}
		template<class... Args>
		reply set::sunionStore(const std::string& destination, Args... keys)
		{
			return cli_.sendSafeCommand("SUNIONSTORE", destination, keys...);
		}
		reply set::scan(const std::string& key,int cursor, const std::string& matchPattern /* = "*" */, int count /* = 10 */)
		{
			return cli_.sendSafeCommand("SSCAN", key, cursor, "MATCH", matchPattern, "COUNT", count);
		}
	};
};