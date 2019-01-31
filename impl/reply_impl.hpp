
#ifndef _CXXREDIS_REPLY_IMPL_HPP_
#define _CXXREDIS_REPLY_IMPL_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <string>
#include <vector>
#include <memory>


namespace redis {

	class replyImpl 
	{
	public:

		enum class replyType
		{
			REPLY_NIL,			//nil
			REPLY_STATUS,		//status
			REPLY_ERROR,		//error
			REPLY_INTEGER,		//int
			REPLY_BULK,			//string
			REPLY_MULTI_BULK,	//array
		};

		typedef std::shared_ptr<replyImpl> replyImplPtr;

		replyImpl()
			:type_(replyType::REPLY_NIL)
		{

		}
		replyImpl(replyType type, const std::string& val) 
			:type_(type),
			val_(val)
		{

		}
		replyImpl(std::vector<replyImplPtr> elements)
			:type_(replyType::REPLY_MULTI_BULK),
			elements_(elements)
		{

		}
			

		bool isarray() const noexcept 
		{
			return type_ == replyType::REPLY_MULTI_BULK;
		}

		bool isinteger() const noexcept
		{
			return type_ == replyType::REPLY_INTEGER;
		}

		bool isstring() const noexcept
		{
			return type_ == replyType::REPLY_BULK;
		}

		bool iserror() const noexcept
		{
			return type_ == replyType::REPLY_ERROR;
		}
		bool isnil() const noexcept
		{
			return type_ == replyType::REPLY_NIL;
		}
		bool isstatus() const noexcept
		{
			return type_ == replyType::REPLY_STATUS;
		}

		long long integer() const
		{
			if (!isinteger())
				throw exception(exception::errorCode::REPLY_VAL_ERROR,"not reply an integer");
			return std::stoll(val_);
		}
		std::string string() const
		{
			if (!isstring() && !isstatus() && !iserror())
				throw exception(exception::errorCode::REPLY_VAL_ERROR,"not reply a string");
			return val_;
		}
		std::vector<replyImplPtr> array() const
		{
			if (!isarray())
				throw exception(exception::errorCode::REPLY_VAL_ERROR,"not reply an array");
			return elements_;
		}

		
		bool ok() const
		{
			if (!isstatus())
				throw exception(exception::errorCode::REPLY_VAL_ERROR,"not reply a status !");
			return val_ == "OK";
		}

	private:

		replyType type_;
		std::string val_;
		std::vector<replyImplPtr> elements_;
	};
};

#endif