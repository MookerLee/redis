
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
	bool reply::isArray() const noexcept
	{
		return impl_->isArray();
	}
	bool reply::isInteger() const noexcept
	{
		return impl_->isInteger();
	}
	bool reply::isString() const noexcept
	{
		return impl_->isString();
	}
	long long reply::asInteger() const
	{
		return impl_->asInteger();
	}
	std::string reply::asString() const
	{
		return impl_->asString();
	}
	std::vector<reply> reply::asArray() const
	{
		impl_->pushImpl(nullptr);

		std::vector<reply> replyArray;

		std::vector<std::shared_ptr<replyImpl>> responseImplArray = impl_->asArray();
		for (auto it = responseImplArray.begin(); it != responseImplArray.end(); ++it)
		{
			replyArray.emplace_back(*it);
		}

		return replyArray;
	}
	bool reply::empty() const noexcept
	{
		return impl_->empty();
	}
	reply::operator bool()
	{
		return asInteger() == RESPONSE_SUCCESS;
	}
	reply::operator std::string()
	{
		return asString();
	}
	reply::operator long long()
	{
		return asInteger();
	}
	bool reply::ok() const
	{
		return impl_->ok();
	}
	bool reply::isStatus() const noexcept
	{
		return impl_->isStatus();
	}
	bool reply::typeSet() const
	{
		return impl_->typeSet();
	}
	bool reply::typeList()const
	{
		return impl_->typeList();
	}
	bool reply::typeNone()const
	{
		return impl_->typeNone();
	}
	bool reply::typeString()const
	{
		return impl_->typeString();
	}
	bool reply::typeZset()const
	{
		return impl_->typeZset();
	}
	bool reply::typeHash()const
	{
		return impl_->typeHash();
	}
};