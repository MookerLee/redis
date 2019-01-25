

#ifndef _CXXREDIS_PROTOCOL_HPP_
#define _CXXREDIS_PROTOCOL_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <memory>
#include <string>

namespace CXXRedis {

	class protocolImpl;
	class reply;

	class protocol {
	public:

		enum replyType
		{
			REPLY_UNKNOW,		//δ֪����
			REPLY_STATUS,		//״̬�ظ���status reply���ĵ�һ���ֽ��� "+"
			REPLY_ERROR,		//����ظ���error reply���ĵ�һ���ֽ��� "-"
			REPLY_INTEGER,		//�����ظ���integer reply���ĵ�һ���ֽ��� ":"
			REPLY_BULK,			//�����ظ���bulk reply���ĵ�һ���ֽ��� "$"
			REPLY_MULTI_BULK,	//���������ظ���multi bulk reply���ĵ�һ���ֽ��� "*"
		};

		protocol();
		~protocol();

		std::string serializeSimpleCommand(const std::string& simpleCommand);

		reply feedBuffer(const std::string& readString);

	private:
		std::shared_ptr<protocolImpl> impl_;
	};
};

#if !defined(CORE_ONLY_HEADER)
#include "impl/protocol.hpp"
#endif

#endif