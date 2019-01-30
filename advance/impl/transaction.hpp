
#include <redis/client.hpp>

namespace redis {
	namespace advance {
		transaction::transaction(client& cli)
			:cli_(cli)
		{

		}
		transaction::~transaction()
		{

		}
		reply transaction::discard()
		{
			return cli_.sendSafeCommand("DISCARD");
		}
		reply transaction::exec()
		{
			return cli_.sendSafeCommand("EXEC");
		}
		reply transaction::multi()
		{
			return cli_.sendSafeCommand("MULTI");
		}
		reply transaction::unwatch()
		{
			return cli_.sendSafeCommand("UNWATCH");
		}
		reply transaction::watch(const std::list<std::string>& keys)
		{
			std::list<std::string> commands{ "WATCH" };
			commands.insert(commands.end(), keys.begin(),keys.end());

			return cli_.sendListCommand(commands);
		}
	};
};