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
		template<class... Args>
		long long srotedSet::add(const std::string& key, std::initializer_list<Args>... scoreMembers)
		{
			return cli_.sendPairsCommand("ZADD", key, scoreMembers...).asInteger();
		}

	};
};