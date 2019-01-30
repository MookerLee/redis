

#ifndef _REDIS_ADVANCE_SERVER_HPP_
#define _REDIS_ADVANCE_SERVER_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

/************************************************************************/
/* 在线文档																*/
/* http://redisdoc.com/server/index.html								*/
/************************************************************************/

#include <functional>

namespace redis {

	class client;
	class reply;

	namespace advance {
		class server {
		public:

			typedef std::function<void(reply)> replyCallBack;

			server(client& cli);
			~server();

			/**
			* 中文
			* http://redisdoc.com/server/bgrewriteaof.html
			* ENGLISH
			* https://redis.io/commands/bgrewriteaof
			*/
			reply bgrewriteaof();

			/**
			* 中文
			* http://redisdoc.com/server/bgsave.html
			* ENGLISH
			* https://redis.io/commands/client-setname
			*/
			reply bgsave();

			/**
			* 中文
			* http://redisdoc.com/server/client_setname.html
			* ENGLISH
			* https://redis.io/commands/client-setname
			*/
			reply clientname();
			reply clientname(const std::string& name);

			/**
			* 中文
			* http://redisdoc.com/server/client_kill.html
			* ENGLISH
			* https://redis.io/commands/client-kill
			*/
			reply clientKill(const std::string& host);

			/**
			* 中文
			* http://redisdoc.com/server/client_list.html
			* ENGLISH
			* https://redis.io/commands/client-list
			*/
			reply clientList();

			/**
			* 中文
			* http://redisdoc.com/server/config_get.html
			* ENGLISH
			* https://redis.io/commands/config-get
			*/
			reply configGet(const std::string& parameter);

			/**
			* 中文
			* http://redisdoc.com/server/config_resetstat.html
			* ENGLISH
			* https://redis.io/commands/config-resetstat
			*/
			reply configrResetState();

			/**
			* 中文
			* http://redisdoc.com/server/config_rewrite.html
			* ENGLISH
			* https://redis.io/commands/config-rewrite
			*/
			reply configRewrite();

			/**
			* 中文
			* http://redisdoc.com/server/config_set.html
			* ENGLISH
			* https://redis.io/commands/config-set
			*/
			reply configSet(const std::string& parameter, const std::string& value);

			/**
			* 中文
			* http://redisdoc.com/server/dbsize.html
			* ENGLISH
			* https://redis.io/commands/dbsize
			*/
			reply dbsize();

			/**
			* 中文
			* http://redisdoc.com/server/debug_object.html
			*/
			reply debugobject(const std::string& key);

			/**
			* 中文
			* http://redisdoc.com/server/debug_segfault.html
			*/
			void debugsegfault();

			/**
			* 中文
			* http://redisdoc.com/server/flushall.html
			* ENGLISH
			* https://redis.io/commands/flushall
			*/
			reply flushall();

			/**
			* 中文
			* http://redisdoc.com/server/flushdb.html
			* ENGLISH
			* https://redis.io/commands/flushdb
			*/
			reply flushdb();

			/**
			* 中文
			* http://redisdoc.com/server/info.html
			* ENGLISH
			* https://redis.io/commands/info
			*/
			reply info();

			/**
			* 中文
			* http://redisdoc.com/server/lastsave.html
			* ENGLISH
			* https://redis.io/commands/lastsave
			*/
			reply lastsave();

			/**
			* 中文
			* http://redisdoc.com/server/monitor.html
			* ENGLISH
			* https://redis.io/commands/monitor
			*/
			void monitor(replyCallBack func);

			/**
			* 中文
			* http://redisdoc.com/server/psync.html
			*/
			reply psync(const std::string& arg1, const std::string& arg2);

			/**
			* 中文
			* http://redisdoc.com/server/save.html
			* ENGLISH
			* https://redis.io/commands/save
			*/
			reply save();

			/**
			* 中文
			* http://redisdoc.com/server/shutdown.html
			* ENGLISH
			* https://redis.io/commands/shutdown
			*/
			reply shutdown(bool save);

			/**
			* 中文
			* http://redisdoc.com/server/slaveof.html。
			* ENGLISH
			* https://redis.io/commands/slaveof
			*/
			reply slaveof(const std::string& host,int port);
			/**
			* COMMAND SLAVEOF NO ONE
			*/
			reply slaveof();

			/**
			* 中文
			* http://redisdoc.com/server/slowlog.html
			* ENGLISH
			* https://redis.io/commands/slowlog
			*/
			reply slowlog(const std::string& subcommand,const std::string& argument = "");

			/**
			* 中文
			* http://redisdoc.com/server/sync.html
			* ENGLISH
			* https://redis.io/commands/sync		
			* MORE
			* https://redis.io/topics/replication
			*/
			reply sync();
		private:
			client& cli_;
		};
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/server.hpp"
#endif

#endif