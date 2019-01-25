
#ifndef _CXXREDIS_REPLY_IMPL_HPP_
#define _CXXREDIS_REPLY_IMPL_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "redis/cxx/exception.hpp"
#include "redis/cxx/protocol.hpp"

#include <string>
#include <vector>
#include <memory>

namespace CXXRedis {

	class replyImpl 
	{
	public:

		replyImpl(protocol::replyType type,const std::string& val)
			:replyType_(type),
			replyVal_(val)
		{
			

		}
		~replyImpl() 
		{
			
		}

		bool isArray() const noexcept
		{
			return replyType_ == protocol::replyType::REPLY_MULTI_BULK;
		}
		bool isInteger() const noexcept
		{
			return replyType_ == protocol::replyType::REPLY_INTEGER;
		}
		bool isString() const noexcept
		{
			return replyType_ == protocol::replyType::REPLY_BULK;
		}

		bool empty() const noexcept
		{
			return !(isArray() || isInteger() || isString());
		}

		long long asInteger() const
		{
			if (!isInteger()) 
				throw exception(
					exception::errorCode::FETCH_REPLY_VAL_ERROR, 
					"not reply integer");

			return std::stoll(replyVal_);
		}
		std::string asString() const
		{
			if (!isString()) 
				throw exception(
					exception::errorCode::FETCH_REPLY_VAL_ERROR, 
					"not reply string");

			return replyVal_;
		}
		std::vector<std::shared_ptr<replyImpl>> asArray() const
		{
			if(!isArray()) 
				throw exception(
					exception::errorCode::FETCH_REPLY_VAL_ERROR, 
					"not reply array");

			return replyImplArray_;
		}

		void pushImpl(std::shared_ptr<replyImpl> impl)
		{
			if(!isArray())
				throw exception(
					exception::errorCode::FETCH_REPLY_VAL_ERROR,
					"push replyImpl fail,not array");

			replyImplArray_.push_back(impl);
		}

		
		bool ok() const 
		{
			if (replyType_ != protocol::REPLY_STATUS) 
				throw exception(
					exception::errorCode::FETCH_REPLY_VAL_ERROR, 
					"not reply status !");

			return replyVal_ == "OK";
		}
	private:

		protocol::replyType replyType_;
		std::string replyVal_;

		std::vector<std::shared_ptr<replyImpl>> replyImplArray_;
	};
};

#endif