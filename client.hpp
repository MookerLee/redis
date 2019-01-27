

#ifndef _CXXREDIS_CLIENT_HPP_
#define _CXXREDIS_CLIENT_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <memory>

namespace redis {

	class clientImpl;
	class reply;

	class client {

	public:
		client();
		~client();

	   /**
		* @ip	redis的IP地址
		* @port redis的端口
		* 如果连接失败会抛 CXXRedis::exception 异常
		*/
		void connect(const std::string& ip, int port);
	   /**
		* 关闭与redis_server 的连接
		*/
		void close();
	   /**
	    * @cmd redis命令
		* @return_value 命令返回的数据
		* 如果命令错误抛 CXXRedis::exception 异常
		*/
		reply sendSimpleCommand(const std::string& cmd);

		template<class... Args>
		reply sendSafeCommand(Args... args);

	   /**
		* @pass redis 密码
		* 抛出异常密码验证失败正常返回表示成功
		*/
		void auth(const std::string& pass);
		/**
		* @message echo信息
		* @return_value 返回 @message
		*/
		std::string echo(const std::string& message);

		/**
		* @return_value true 正常
		*/
		bool ping();

		void select(int db);
	private:

		// The implementation.
		std::shared_ptr<clientImpl> impl_;
	};
};
#if !defined(CORE_ONLY_HEADER)
#include "impl/client.hpp"
#endif

#endif