
#include "response_impl.hpp"

namespace CXXRedis {
	response::response()
		:impl_(nullptr)
	{

	}
	response::response(std::shared_ptr<responseImpl> impl)
		:impl_(impl)
	{

	}
	response::~response()
	{
		
	}
	bool response::isArray() const noexcept
	{
		return impl_->isArray();
	}
	bool response::isInteger() const noexcept
	{
		return impl_->isInteger();
	}
	bool response::isString() const noexcept
	{
		return impl_->isString();
	}
	long long response::asInteger() const
	{
		return impl_->asInteger();
	}
	std::string response::asString() const
	{
		return impl_->asString();
	}
	std::vector<response> response::asArray() const
	{
		std::vector<response> responseArray;

		std::vector<std::shared_ptr<responseImpl>> responseImplArray = impl_->asArray();
		for (auto it = responseImplArray.begin(); it != responseImplArray.end(); ++it)
		{
			responseArray.emplace_back(*it);
		}

		return responseArray;
	}
	bool response::empty() const noexcept
	{
		return impl_->empty();
	}

};