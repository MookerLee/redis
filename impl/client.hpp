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
		return reply(impl_->send(cmd));
	}
	void client::auth(const std::string& pass)
	{
		sendSafeCommand("AUTH", pass);
	}
	std::string client::echo(const std::string& message)
	{
		return sendSafeCommand("ECHO", message).asString();
	}
	bool client::ping()
	{
		return sendSafeCommand("PING").asString() == "PONG";
	}
	void client::select(int db)
	{
		sendSafeCommand("SELECT", db);
	}

	template <class... Args>
	reply client::sendSafeCommand(Args... args)
	{
		return reply(impl_->sendSafeCommand(args...));
	}
	template<class... Args>
	reply client::sendPairsCommand(const std::string& cmd, std::initializer_list<Args>... pairs)
	{
		return reply(impl_->sendPairsCommand(cmd, pairs...));
	}
	template<class... Args>
	reply client::sendPairsCommand(const std::string& cmd, const std::string& key, std::initializer_list<Args>... pairs)
	{
		return reply(impl_->sendPairsCommand(cmd,key, pairs...));
	}
};