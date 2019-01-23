#include "client_impl.hpp"

namespace CXXRedis 
{
	client::client():impl_(std::make_shared<clientImpl>())
	{

	}
	client::~client()
	{
		
	}
	void client::connect(const std::string& ip, int port)
	{
		return impl_->connect(ip, port);
	}
	void client::close()
	{
		send("QUIT");
		return impl_->close();
	}
	response client::send(const std::string& cmd)
	{
		return response(impl_->send(cmd));
	}
	void client::auth(const std::string& pass)
	{
		send(format::formatCmd("AUTH", pass));
	}
	std::string client::echo(const std::string& message)
	{
		return send(format::formatCmd("ECHO", message)).asString();
	}
	bool client::ping()
	{
		return send("PING").asString() == "PONG";
	}
	void client::select(int db)
	{
		send(format::formatCmd("SELECT", db));
	}
};