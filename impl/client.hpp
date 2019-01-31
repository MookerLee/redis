#include "client_impl.hpp"

namespace redis 
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
		sendSafeCommand("QUIT");
	}
	reply client::sendSimpleCommand(const std::string& cmd)
	{
		return reply(impl_->sendSimpleCommand(cmd));
	}
	void client::auth(const std::string& pass)
	{
		sendSafeCommand("AUTH", pass);
	}
	std::string client::echo(const std::string& message)
	{
		return sendSafeCommand("ECHO", message).string();
	}
	bool client::ping()
	{
		return sendSafeCommand("PING").string() == "PONG";
	}
	void client::select(int db)
	{
		sendSafeCommand("SELECT", db);
	}

	template <class... Args>
	reply client::sendSafeCommand(const std::string& cmd,Args... args)
	{
		return reply(impl_->sendSafeCommand(cmd,args...));
	}


	reply client::sendListCommand(const std::list<std::string>& commands)
	{
		return reply(impl_->sendListCommand(commands));
	}
};