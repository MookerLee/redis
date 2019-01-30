
#ifndef _REDIS_ADVANCE_GEO_HPP_
#define _REDIS_ADVANCE_GEO_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

/************************************************************************/
/* 在线文档																*/
/* http://redisdoc.com/geo/index.html								*/
/************************************************************************/

namespace redis {

	class client;
	class reply;

	namespace advance {

		class geo {
		public:

			struct element 
			{
				std::string longitude, latitude, member;
			};

			geo(client& cli);
			~geo();

			/**
			* 中文
			* http://redisdoc.com/geo/geoadd.html
			* ENGLISH
			* https://redis.io/commands/geoadd
			*/
			reply geoadd(const std::string& key,const std::list<element>& elements);

			/**
			* 中文
			* http://redisdoc.com/geo/geopos.html
			* ENGLISH
			* https://redis.io/commands/geopos
			*/
			reply geopos(const std::string& key, const std::list<std::string>& members);

			/**
			* 中文
			* http://redisdoc.com/geo/geodist.html
			* ENGLISH
			* https://redis.io/commands/geodist
			*/
			reply geodist(const std::string& key,
				const std::string& member1,
				const std::string& member2,
				const std::string& unit = "m");

			/**
			* 中文
			* http://redisdoc.com/geo/georadius.html
			* ENGLISH
			* https://redis.io/commands/georadius
			*/
			reply georadius(const std::string& key,
				const std::string& longitude,
				const std::string& latitude, 
				const std::string& radius, 
				const std::string& unit = "m",
				bool withcoord = false,
				bool withdist = false,
				bool withhash = false,
				bool asc = true,
				int count = 100);

			/**
			* 中文
			* http://redisdoc.com/geo/georadiusbymember.html
			* ENGLISH
			* https://redis.io/commands/georadiusbymember
			*/
			reply georadiusbymember(
				const std::string& key,
				const std::string& member,
				const std::string& radius,
				const std::string& unit = "m",
				bool withcoord = false,
				bool withdist = false,
				bool withhash = false,
				bool asc = true,
				int count = 100);

			/**
			* 中文
			* http://redisdoc.com/geo/geohash.html
			* ENGLISH
			* https://redis.io/commands/geohash
			*/
			reply geohash(const std::string& key, const std::list<std::string>& members);
		private:
			client& cli_;
		};
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/geo.hpp"
#endif

#endif