
#include "connection_impl.hpp"

namespace CXXRedis {
	connection::connection()
		:impl_(std::make_shared<connectionImpl>())
	{

	}
	connection::~connection()
	{

	}
	void connection::connect(const std::string& host, int port)
	{
		impl_->connect(host, port);
	}
	void connection::send(const void* buff, size_t bytes)
	{
		impl_->send(buff, bytes);
	}
	std::string connection::read()
	{
		return impl_->read();
	}
};