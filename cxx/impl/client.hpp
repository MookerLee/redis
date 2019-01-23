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
		return impl_->close();
	}
	response client::send(const std::string& cmd)
	{
		return response(impl_->send(cmd));
	}
};