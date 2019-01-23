

#ifndef _REDIS_CLIENT_H_
#define _REDIS_CLIENT_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <memory>
#include "format.hpp"

namespace CXXRedis {

	class clientImpl;
	class response;

	class client {

	public:
		class key;
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
		response send(const std::string& cmd);

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

	class client::key{

	public:
		key(client& cli);
		~key();

		template<class... Args>
		int del(Args... keys) 
		{
			return cli_.send(format::formatCmd("DEL", keys...)).asInteger();
		}
		response dump(const std::string& k);
		bool exists(const std::string& k);

	   /**
		* 为给定 key 设置生存时间，当 key 过期时(生存时间为 0 )，它会被自动删除。
		*/
		bool expire(const std::string& k,int second);
	   /**
		* EXPIREAT 的作用和 EXPIRE 类似，都用于为 key 设置生存时间。
		*/
		bool expireat(const std::string& k, time_t timestamp);
	   /**
		* 查找所有符合给定模式 pattern 的 key 
		*/
		response keys(const std::string& pattern);
		response keys();
	   /**
		* 将 key 原子性地从当前实例传送到目标实例的指定数据库上，一旦传送成功， key 保证会出现在目标实例上，而当前实例上的 key 会被删除。
		*/
		void migrate(const std::string& host, int port, const std::string& k, int db, time_t milliseconds);
	   /**
		* 将当前数据库的 key 移动到给定的数据库 db 当中。
		*/
		bool move(const std::string& k, int db);
	   /**
		* 返回给定 key 引用所储存的值的次数。此命令主要用于除错。
		*/
		long long objectRefcount(const std::string& k);
		/**
		* 返回给定 key 自储存以来的空转时间(idle， 没有被读取也没有被写入)，以秒为单位。
		*/
		long long objectIdleTime(const std::string& k);
		/**
		* 返回给定 key 锁储存的值所使用的内部表示(representation)
		*/
		std::string objectEncoding(const std::string& k);
	private:
		
		
	private:
		client& cli_;
	};
};
#if !defined(CORE_ONLY_HEADER)
#include "impl/client.hpp"
#include "impl/client_key.hpp"
#endif

#endif