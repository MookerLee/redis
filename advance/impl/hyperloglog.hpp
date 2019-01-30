#include <redis/client.hpp>

namespace redis {
	namespace advance {

		hyperloglog::hyperloglog(client& cli)
			:cli_(cli)
		{

		}
		hyperloglog::~hyperloglog()
		{

		}
		reply hyperloglog::pfadd(const std::string& key, const std::list<std::string>& elements)
		{
			std::list<std::string> commands{"PFADD",key};
			commands.insert(commands.end(), elements.begin(), elements.end());
			return cli_.sendListCommand(commands);
		}
		reply hyperloglog::pfcount(const std::list<std::string>& keys)
		{
			std::list<std::string> commands{ "PFCOUNT" };
			commands.insert(commands.end(), keys.begin(), keys.end());
			return cli_.sendListCommand(commands);
		}
		reply hyperloglog::pfmerge(const std::string& key, const std::list<std::string>& sourcekeys)
		{
			std::list<std::string> commands{ "PFMERGE",key };
			commands.insert(commands.end(), sourcekeys.begin(), sourcekeys.end());
			return cli_.sendListCommand(commands);
		}
	};
};