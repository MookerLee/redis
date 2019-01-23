
#ifndef _CXXREDIS_RESPONSE_IMPL_HPP_
#define _CXXREDIS_RESPONSE_IMPL_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "redis/hiredis/hiredis.h"
#include "redis/cxx/exception.hpp"

#include <string>
#include <vector>
#include <memory>

namespace CXXRedis {

	class responseImpl 
	{
	public:
		responseImpl(
			int type = REDIS_REPLY_NIL, 
			long long integer = 0, 
			const std::string& str = ""):type_(type),integer_(integer),str_(str) {}

		~responseImpl() 
		{
			
		}

		bool isArray() const noexcept
		{
			return type_ == REDIS_REPLY_ARRAY;
		}
		bool isInteger() const noexcept
		{
			return type_ == REDIS_REPLY_INTEGER;
		}
		bool isString() const noexcept
		{
			return type_ == REDIS_REPLY_STRING;
		}

		bool empty() const noexcept
		{
			return !(isArray() || isInteger() || isString());
		}

		long long asInteger() const
		{
			if (!isInteger()) throw exception(-1, "response not a integer");
			return integer_;
		}
		std::string asString() const
		{
			if (!isString()) throw exception(-1, "response not a string");
			return str_;
		}
		std::vector<std::shared_ptr<responseImpl>> asArray() const
		{
			if(!isArray()) throw exception(-1, "response not an array");
			return responseImplArray_;
		}

		void push(std::shared_ptr<responseImpl> res)
		{
			responseImplArray_.push_back(res);
		}

		static std::shared_ptr<responseImpl> createResponseImpl(redisReply* reply)
		{
			auto  resImpl = std::make_shared<responseImpl>(reply->type, reply->integer, std::string(reply->str, reply->len));

			if (reply->type == REDIS_REPLY_ARRAY) 
			{
				for (size_t i = 0; i < reply->elements; ++i) 
				{

					resImpl->push(
						std::make_shared<responseImpl>(
							reply->element[i]->type,
							reply->element[i]->integer,
							std::string(reply->element[i]->str, reply->element[i]->len))
					);
				}
			}
			return resImpl;
		}
		
	private:

		int type_;
		long long integer_;
		std::string str_;

		std::vector<std::shared_ptr<responseImpl>> responseImplArray_;
	};
};

#endif