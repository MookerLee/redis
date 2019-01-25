#include "protocol_impl.hpp"
//#include "redis/cxx/reply.hpp"

namespace CXXRedis {

	protocol::protocol()
		:impl_(std::make_shared<protocolImpl>())
	{

	}
	protocol::~protocol()
	{

	}
	std::string protocol::serializeSimpleCommand(const std::string& simpleCommand)
	{
		return impl_->serializeSimpleCommand(simpleCommand);
	}
	reply protocol::feedBuffer(const std::string& readString)
	{
		return reply(impl_->feedBuffer(readString));
	}

};