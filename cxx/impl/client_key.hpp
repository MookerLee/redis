
#include<sstream>

#define OP_KEY_SUCCESS 1

namespace CXXRedis {
	client::key::key(client& cli)
		:cli_(cli)
	{

	}
	client::key::~key()
	{

	}
	response client::key::dump(const std::string& k)
	{
		 return cli_.send(format::formatCmd("DUMP", k));
	}
	bool client::key::exists(const std::string& k)
	{
		return cli_.send(format::formatCmd("EXISTS", k)).asInteger() == OP_KEY_SUCCESS;
	}
	bool client::key::expire(const std::string& k, int second)
	{
		return cli_.send(format::formatCmd("EXPIRE", k,second)).asInteger() == OP_KEY_SUCCESS;
	}
	bool client::key::expireat(const std::string& k, time_t timestamp)
	{
		return cli_.send(format::formatCmd("EXPIREAT", k, timestamp)).asInteger() == OP_KEY_SUCCESS;
	}
	response client::key::keys(const std::string& pattern)
	{
		return cli_.send(format::formatCmd("KEYS", pattern));
	}
	response client::key::keys()
	{
		return keys("*");
	}
	void client::key::migrate(const std::string& host, int port, const std::string& k, int db, time_t milliseconds)
	{
		cli_.send(format::formatCmd("MIGRATE", host, port, k, db, milliseconds));
	}
	bool client::key::move(const std::string& k, int db)
	{
		return cli_.send(format::formatCmd("MOVE", k, db)).asInteger() == OP_KEY_SUCCESS;
	}
	long long client::key::objectRefcount(const std::string& k)
	{
		return cli_.send(format::formatCmd("OBJECT REFCOUNT", k)).asInteger();
	}
	long long client::key::objectIdleTime(const std::string& k)
	{
		return cli_.send(format::formatCmd("OBJECT IDLETIME", k)).asInteger();
	}
	std::string client::key::objectEncoding(const std::string& k)
	{
		return cli_.send(format::formatCmd("OBJECT ENCODING", k)).asString();
	}
};