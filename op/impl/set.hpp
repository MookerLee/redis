
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
	}
}