
#include <redis/client.hpp>

namespace redis {
	namespace advance {
		script::script(client& cli)
			:cli_(cli)
		{

		}
		script::~script()
		{

		}
		reply script::eval(const std::string& scriptStr,
			const std::list<std::string>& keys,
			const std::list<std::string>& args)
		{
			std::list<std::string> commands{ "EVAL",scriptStr };
			commands.push_back(std::to_string(keys.size()));
			commands.insert(commands.end(), keys.begin(), keys.end());
			commands.insert(commands.end(), args.begin(), args.end());

			return cli_.sendListCommand(commands);
		}

		reply script::evalsha(const std::string& sha1,
			const std::list<std::string>& keys,
			const std::list<std::string>& args)
		{
			std::list<std::string> commands{ "EVALSHA",sha1 };
			commands.push_back(std::to_string(keys.size()));
			commands.insert(commands.end(), keys.begin(), keys.end());
			commands.insert(commands.end(), args.begin(), args.end());

			return cli_.sendListCommand(commands);
		}

		reply script::scriptExists(const std::list<std::string>& sha1s)
		{
			std::list<std::string> commands{ "SCRIPT","EXISTS" };
			commands.insert(commands.end(), sha1s.begin(), sha1s.end());
			return cli_.sendListCommand(commands);
		}

		reply script::scriptFlush()
		{
			return cli_.sendSafeCommand("SCRIPT", "FLUSH");
		}
		reply script::scriptKill()
		{
			return cli_.sendSafeCommand("SCRIPT", "KILL");
		}

		reply script::scriptLoad(const std::string& scriptStr)
		{
			return cli_.sendSafeCommand("SCRIPT", "LOAD",scriptStr);
		}
	};
};