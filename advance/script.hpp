

#ifndef _REDIS_ADVANCE_SCRIPT_HPP_
#define _REDIS_ADVANCE_SCRIPT_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

/************************************************************************/
/* �����ĵ�																*/
/* http://redisdoc.com/script/index.html								*/
/************************************************************************/

#include <string>
#include <list>

namespace redis {

	class client;
	class reply;

	namespace advance {
		class script {
		public:
			script(client& cli);
			~script();

			/**
			* ����
			* http://redisdoc.com/script/eval.html
			* ENGLISH
			* https://redis.io/commands/eval
			*/
			reply eval(const std::string& scriptStr,
				const std::list<std::string>& keys,
				const std::list<std::string>& args);

			/**
			* ����
			* http://redisdoc.com/script/evalsha.html
			* ENGLISH
			* https://redis.io/commands/evalsha
			*/
			reply evalsha(const std::string& sha1,
				const std::list<std::string>& keys,
				const std::list<std::string>& args);

			/**
			* ����
			* http://redisdoc.com/script/script_exists.html
			* ENGLISH
			* https://redis.io/commands/script-exists
			*/
			reply scriptExists(const std::list<std::string>& sha1s);

			/**
			* ����
			* http://redisdoc.com/script/script_flush.html
			* ENGLISH
			* https://redis.io/commands/script-flush
			*/
			reply scriptFlush();

			/**
			* ����
			* http://redisdoc.com/script/script_kill.html
			* ENGLISH
			* https://redis.io/commands/script-kill
			*/
			reply scriptKill();

			/**
			* ����
			* http://redisdoc.com/script/script_load.html
			* ENGLISH
			* https://redis.io/commands/script-load
			*/
			reply scriptLoad(const std::string& scriptStr);
		private:
			client& cli_;
		};
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/script.hpp"
#endif

#endif