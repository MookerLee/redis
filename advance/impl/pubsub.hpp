
#include <redis/client.hpp>

namespace redis {
	namespace advance {
		pubsub::pubsub(client& cli)
			:cli_(cli)
		{

		}
		pubsub::~pubsub()
		{

		}

		reply pubsub::psubscribe(const std::list<std::string>& patterns)
		{
			std::list<std::string> commands{ "PSUBSCRIBE" };
			commands.insert(commands.end(),patterns.begin(), patterns.end());
			return cli_.sendListCommand(commands);
		}

		reply pubsub::publish(const std::string& channel, const std::string& message)
		{
			return cli_.sendSafeCommand("PUBLISH", channel, message);
		}

		reply pubsub::pubSub(const std::string& subcommand, const std::list<std::string>& arguments)
		{
			std::list<std::string> commands{ "PUBSUB",subcommand };
			commands.insert(commands.end(), arguments.begin(), arguments.end());
			return cli_.sendListCommand(commands);
		}
		reply pubsub::punsubscribe(const std::list<std::string>& patterns)
		{
			std::list<std::string> commands{ "PUNSUBSCRIBE" };
			commands.insert(commands.end(), patterns.begin(), patterns.end());
			return cli_.sendListCommand(commands);
		}
		reply pubsub::subscribe(const std::list<std::string>& channels)
		{
			std::list<std::string> commands{ "SUBSCRIBE" };
			commands.insert(commands.end(), channels.begin(), channels.end());
			return cli_.sendListCommand(commands);
		}
		reply pubsub::unsubscribe(const std::list<std::string>& channels)
		{
			std::list<std::string> commands{ "UNSUBSCRIBE" };
			commands.insert(commands.end(), channels.begin(), channels.end());
			return cli_.sendListCommand(commands);
		}
	};
};