#pragma once

#ifndef _REDIS_CLIENT_IMPL_H_
#define _REDIS_CLIENT_IMPL_H_

#include "redis/hiredis/hiredis.h"
#include "redis/cxx/exception.hpp"
#include "redis/cxx/response.hpp"
#include "response_impl.hpp"

#include <string>
#include <cassert>


namespace CXXRedis {

class clientImpl {

public:

	clientImpl() :redisContext_(nullptr) {}
	~clientImpl() 
	{
		close();
	}

	void connect(const std::string& ip, int port) 
	{

		struct timeval timeout = { 1, 500000 }; // 1.5 seconds

		redisContext_ = redisConnectWithTimeout(ip.c_str(), port, timeout);
		if (redisContext_->err) {
			close();
			throw exception(redisContext_->err,
				redisContext_->errstr);
		}
	}

	std::shared_ptr<responseImpl> send(const std::string& cmd)
	{

		redisReply *reply = (redisReply*)redisCommand(redisContext_, cmd.c_str());

		if (reply == nullptr) 
		{
			assert(false);
			throw exception(REDIS_ERR_OOM, "out of memory");
		}

		if (reply->type == REDIS_REPLY_ERROR)
		{
			freeReplyObject(reply);
			throw exception(REDIS_REPLY_ERROR, std::string(reply->str, reply->len));
		}

		//返回 REDIS_REPLY_NIL ，说明不存在要访问的数据。
		if (reply->type == REDIS_REPLY_NIL) 
		{
			freeReplyObject(reply);
			throw exception(REDIS_REPLY_NIL, "key is not exist");
		}

		if (reply->type == REDIS_REPLY_STATUS) {
			if (std::string(reply->str, reply->len) != "OK")
			{
				freeReplyObject(reply);
				throw exception(REDIS_REPLY_STATUS, std::string(reply->str, reply->len));
			}		
		}

		std::shared_ptr<responseImpl> res = nullptr;

		if (reply != nullptr)
		{
			res = responseImpl::createResponseImpl(reply);
			freeReplyObject(reply);
		}

		return res;
	}
	void close() 
	{
		if (redisContext_) 
		{
			redisFree(redisContext_);
			redisContext_ = nullptr;
		} 
			
	}
private:
	redisContext* redisContext_;
};
};

#endif