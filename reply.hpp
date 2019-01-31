
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
		* �жϷ����Ƿ�Ϊ����
		*/
		bool isarray() const noexcept;

		/**
		* �жϷ����Ƿ�Ϊ����
		*/
		bool isinteger() const noexcept;

		/**
		* �жϷ����Ƿ�Ϊ�ַ���
		*/
		bool isstring() const noexcept;

		/**
		* �жϷ����Ƿ�Ϊ״̬
		*/
		bool isstatus() const noexcept;

		/**
		* �жϷ�����nil
		*/
		bool isnil() const noexcept;

		/**
		* �жϷ�����error
		*/
		bool iserror() const noexcept;

		/**
		* ��ȡ����ֵ
		*/
		long long integer() const;

		/**
		* ��ȡ�ַ���
		*/
		std::string string() const;

		/**
		* ��ȡ����
		*/
		std::vector<reply> array() const;


		/**
		* ״̬�Ƿ�ΪOK
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