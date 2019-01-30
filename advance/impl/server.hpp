#include <redis/client.hpp>

namespace redis {
	namespace advance {
		server::server(client& cli)
			:cli_(cli)
		{

		}
		server::~server()
		{

		}
		reply server::bgrewriteaof()
		{
			return cli_.sendSafeCommand("BGREWRITEAOF");
		}
		reply server::bgsave()
		{
			return cli_.sendSafeCommand("BGSAVE");
		}
		reply server::clientname()
		{
			return cli_.sendSafeCommand("CLIENT","GETNAME");
		}
		reply server::clientname(const std::string& name)
		{
			return cli_.sendSafeCommand("CLIENT", "SETNAME",name);
		}
		reply server::clientKill(const std::string& host)
		{
			return cli_.sendSafeCommand("CLIENT", "KILL", host);
		}
		reply server::clientList()
		{
			return cli_.sendSafeCommand("CLIENT", "LIST");
		}
		reply server::configGet(const std::string& parameter)
		{
			return cli_.sendSafeCommand("CONFIG", "GET", parameter);
		}
		reply server::configrResetState()
		{
			return cli_.sendSafeCommand("CONFIG", "RESETSTAT");
		}
		reply server::configRewrite()
		{
			return cli_.sendSafeCommand("CONFIG", "REWRITE");
		}
		reply server::configSet(const std::string& parameter, const std::string& value)
		{
			return cli_.sendSafeCommand("CONFIG", "SET",parameter,value);
		}
		reply server::dbsize()
		{
			return cli_.sendSafeCommand("DBSIZE");
		}
		reply server::debugobject(const std::string& key)
		{
			return cli_.sendSafeCommand("DEBUG","OBJECT",key);
		}
		void server::debugsegfault()
		{
			cli_.sendSafeCommand("DEBUG", "SEGFAULT");
		}
		reply server::flushall()
		{
			return cli_.sendSafeCommand("FLUSHALL");
		}
		reply server::flushdb()
		{
			return cli_.sendSafeCommand("FLUSHDB");
		}
		reply server::info()
		{
			return cli_.sendSafeCommand("INFO");
		}
		reply server::lastsave()
		{
			return cli_.sendSafeCommand("LASTSAVE");
		}
		void server::monitor(replyCallBack func)
		{
			while (true)
			{
				func(cli_.sendSafeCommand("MONITOR"));
			}
		}
		reply server::psync(const std::string& arg1, const std::string& arg2)
		{
			return cli_.sendSafeCommand("PSYNC",arg1,arg2);
		}
		reply server::save()
		{
			return cli_.sendSafeCommand("SAVE");
		}
		reply server::shutdown(bool save)
		{
			std::list<std::string> commands{ "SHUTDOWN" };
			if (save) commands.push_back("SAVE");
			else commands.push_back("NOSAVE");

			return cli_.sendListCommand(commands);
		}

		reply server::slaveof(const std::string& host, int port)
		{
			return cli_.sendSafeCommand("SLAVEOF",host,port);
		}
		reply server::slaveof()
		{
			return cli_.sendSafeCommand("SLAVEOF", "NO", "ONE");
		}
		reply server::slowlog(const std::string& subcommand, const std::string& argument /* = "" */)
		{
			std::list<std::string> commands{ "SLOWLOG",subcommand };
			if (!argument.empty()) commands.push_back(argument);
			return cli_.sendListCommand(commands);
		}
		reply server::sync()
		{
			return cli_.sendSafeCommand("SYNC");
		}
	};
};