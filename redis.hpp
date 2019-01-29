#ifndef _CXXREDIS_REDIS_HPP_
#define _CXXREDIS_REDIS_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <list>
#include <string>

namespace redis
{
	typedef std::list<std::string> commandList;
};

#include <redis/client.hpp>
#include <redis/reply.hpp>
#include <redis/exception.hpp>
#include <redis/op/key.hpp>
#include <redis/op/string.hpp>
#include <redis/op/hash.hpp>
#include <redis/op/list.hpp>
#include <redis/op/set.hpp>
#include <redis/op/sroted_set.hpp>

#endif