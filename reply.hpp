
#ifndef _REDIS_REPLY_HPP_
#define _REDIS_REPLY_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <memory>
#include <vector>

namespace redis {

	class replyImpl;

	class reply{	
	public:

		reply();
		reply(std::shared_ptr<replyImpl> impl);

		~reply();

		/**
		* 判断返回是否为数组
		*/
		bool isarray() const noexcept;

		/**
		* 判断返回是否为整数
		*/
		bool isinteger() const noexcept;

		/**
		* 判断返回是否为字符串
		*/
		bool isstring() const noexcept;

		/**
		* 判断返回是否为状态
		*/
		bool isstatus() const noexcept;

		/**
		* 判断返回是nil
		*/
		bool isnil() const noexcept;

		/**
		* 判断返回是error
		*/
		bool iserror() const noexcept;

		/**
		* 获取整数值
		*/
		long long integer() const;

		/**
		* 获取字符串
		*/
		std::string string() const;

		/**
		* 获取数组
		*/
		std::vector<reply> array() const;


		/**
		* 状态是否为OK
		*/
		bool ok() const;

		operator long long();
		operator std::string();

	private:
		std::shared_ptr<replyImpl> impl_;
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "redis/impl/reply.hpp"
#endif

#endif