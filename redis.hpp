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
#include <redis/container/key.hpp>
#include <redis/container/string.hpp>
#include <redis/container/hash.hpp>
#include <redis/container/list.hpp>
#include <redis/container/set.hpp>
#include <redis/container/srotedset.hpp>


#include <redis/advance/server.hpp>
#include <redis/advance/script.hpp>

#endif