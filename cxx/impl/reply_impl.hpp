
#ifndef _CXXREDIS_REPLY_IMPL_HPP_
#define _CXXREDIS_REPLY_IMPL_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <string>
#include <vector>
#include <memory>


namespace CXXRedis {

	class replyImpl 
	{
	public:

		enum replyType
		{
			REPLY_UNKNOW,
			REPLY_STATUS,		//状态回复
			REPLY_ERROR,		//错误回复
			REPLY_INTEGER,		//整数回复
			REPLY_BULK,			//批量回复
			REPLY_MULTI_BULK,	//多条批量回复
		};

		typedef std::shared_ptr<replyImpl> replyImplPtr;

		replyImpl(replyType type, const std::string& val) 
			:replyType_(type),
			replyVal_(val)
		{

		}
			

		bool isArray() const noexcept 
		{
			return replyType_ == replyType::REPLY_MULTI_BULK;
		}

		bool isInteger() const noexcept
		{
			return replyType_ == replyType::REPLY_INTEGER;
		}

		bool isString() const noexcept
		{
			return replyType_ == replyType::REPLY_BULK;
		}

		bool empty() const noexcept
		{
			return !(isArray() || isInteger() || isString());
		}

		long long asInteger() const
		{
			if (!isInteger())
				throw exception(
					exception::errorCode::REPLY_VAL_ERROR,
					"not reply integer");

			return std::stoll(replyVal_);
		}
		std::string asString() const
		{
			if (!isString())
				throw exception(
					exception::errorCode::REPLY_VAL_ERROR,
					"not reply string");

			return replyVal_;
		}
		std::vector<replyImplPtr> asArray() const
		{
			if (!isArray())
				throw exception(
					exception::errorCode::REPLY_VAL_ERROR,
					"not reply array");

			return replyImplArray_;
		}

		void pushImpl(replyImplPtr impl)
		{
			if (!isArray())
				throw exception(
					exception::errorCode::REPLY_VAL_ERROR,
					"push replyImpl fail,not array");

			replyImplArray_.push_back(impl);
		}

		
		bool ok() const
		{
			if (replyType_ != replyType::REPLY_STATUS)
				throw exception(
					exception::errorCode::REPLY_VAL_ERROR,
					"not reply status !");

			return replyVal_ == "OK";
		}

		bool error() const 
		{
			return replyType_ == replyType::REPLY_ERROR;
		}
	private:

		replyType replyType_;
		std::string replyVal_;

		std::vector<replyImplPtr> replyImplArray_;
	};
};

#endif