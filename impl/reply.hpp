
#include "reply_impl.hpp"

#define RESPONSE_SUCCESS 1

namespace redis {
	reply::reply()
		:impl_(nullptr)
	{

	}
	reply::reply(std::shared_ptr<replyImpl> impl)
		:impl_(impl)
	{

	}
	reply::~reply()
	{
		
	}
	bool reply::iserror() const noexcept
	{
		return impl_->iserror();
	}
	bool reply::isarray() const noexcept
	{
		return impl_->isarray();
	}
	bool reply::isinteger() const noexcept
	{
		return impl_->isinteger();
	}
	bool reply::isstring() const noexcept
	{
		return impl_->isstring();
	}
	long long reply::integer() const
	{
		return impl_->integer();
	}
	std::string reply::string() const
	{
		return impl_->string();
	}
	std::vector<reply> reply::array() const
	{
		std::vector<reply> replyArray;

		std::vector<std::shared_ptr<replyImpl>> responseImplArray = impl_->array();
		for (auto it = responseImplArray.begin(); it != responseImplArray.end(); ++it)
		{
			replyArray.emplace_back(*it);
		}

		return replyArray;
	}
	bool reply::isnil() const noexcept
	{
		return impl_->isnil();
	}
	reply::operator std::string()
	{
		return string();
	}
	reply::operator long long()
	{
		return integer();
	}
	bool reply::ok() const
	{
		return impl_->ok();
	}
	bool reply::isstatus() const noexcept
	{
		return impl_->isstatus();
	}
};