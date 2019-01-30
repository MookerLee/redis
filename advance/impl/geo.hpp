
#include <redis/client.hpp>

namespace redis {
	namespace advance {
		geo::geo(client& cli)
			:cli_(cli)
		{

		}
		geo::~geo()
		{

		}

		reply geo::geoadd(const std::string& key,const std::list<element>& elements)
		{
			std::list<std::string> commands{ "GEOADD",key };

			for (const auto& e : elements)
			{
				commands.push_back(e.longitude);
				commands.push_back(e.latitude);
				commands.push_back(e.member);
			}

			return cli_.sendListCommand(commands);
		}
		reply geo::geopos(const std::string& key, const std::list<std::string>& members)
		{
			std::list<std::string> commands{ "GEOPOS",key };
			commands.insert(commands.end(), members.begin(), members.end());
			return cli_.sendListCommand(commands);
		}
		reply geo::geodist(const std::string& key, 
			const std::string& member1, 
			const std::string& member2, 
			const std::string& unit /* = "m" */)
		{
			return cli_.sendSafeCommand("GEODIST",key,member1,member2,unit);
		}
		reply geo::georadius(const std::string& key,
			const std::string& longitude,
			const std::string& latitude,
			const std::string& radius,
			const std::string& unit /* = "m" */,
			bool withcoord /* = false */,
			bool withdist /* = false */,
			bool withhash /* = false */,
			bool asc /* = true */,
			int count /* = 100 */)
		{
			std::list<std::string> commands{ "GEORADIUS",key,longitude,latitude,radius,unit };
			if (withcoord) commands.push_back("WITHCOORD");
			if (withdist) commands.push_back("WITHDIST");
			if (withhash) commands.push_back("WITHHASH");
			if (asc) commands.push_back("ASC");
			else commands.push_back("DESC");

			commands.push_back(std::to_string(count));

			return cli_.sendListCommand(commands);
		}

		reply geo::georadiusbymember(const std::string& key,
			const std::string& member,
			const std::string& radius,
			const std::string& unit /* = "m" */,
			bool withcoord /* = false */,
			bool withdist /* = false */,
			bool withhash /* = false */,
			bool asc /* = true */,
			int count /* = 100 */)
		{
			std::list<std::string> commands{ "GEORADIUSBYMEMBER",key,member,radius,unit };
			if (withcoord) commands.push_back("WITHCOORD");
			if (withdist) commands.push_back("WITHDIST");
			if (withhash) commands.push_back("WITHHASH");
			if (asc) commands.push_back("ASC");
			else commands.push_back("DESC");

			commands.push_back(std::to_string(count));

			return cli_.sendListCommand(commands);
		}
		reply geo::geohash(const std::string& key, const std::list<std::string>& members)
		{
			std::list<std::string> commands{ "GEOHASH",key};
			commands.insert(commands.end(), members.begin(), members.end());
			return cli_.sendListCommand(commands);
		}
	};	
};