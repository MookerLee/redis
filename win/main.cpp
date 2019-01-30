#include <iostream>
#include <redis/redis.hpp>

void func(redis::reply r)
{

}
int main()
{
	try
	{
		redis::client cli;
		cli.connect(/*"192.168.1.30", 6379*/);

		//redis::reply rep = cli.sendSimpleCommand("CLIENT GETNAME");
		//std::cout << rep.asString();

		redis::container::string k(cli);
		//k.get("ff");

		redis::advance::server sev(cli);
		sev.clientList();

		redis::advance::script sr(cli);

		for(int i= 0;i<10;++i)
		sev.monitor(func);
		//sev.debugsegfault();
		//redis::op::hash h(cli);
		//h.hvals("gg");

		redis::container::srotedset st(cli);
		st.zscan("kk");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	

	system("pause");
	return 0;
}
