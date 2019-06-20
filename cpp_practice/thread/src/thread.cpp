#include <iostream>
#include <thread>
#include <unistd.h>


void timer(int n)
{
	std::cout<<"wait "<< n << " secs"<<std::endl;
	for (int i=1; i < n + 1; i++)
	{
		std::cout<< i <<" secs"<<std::endl;
		sleep(1);
	}
}
  
int main()
{
    std::thread t(timer, 10);
    std::cout << "before joining,joinable=" << std::boolalpha << t.joinable() << std::endl;
    t.join();
    std::cout << "after joining, joinable=" << std::boolalpha << t.joinable() << '\n';
}