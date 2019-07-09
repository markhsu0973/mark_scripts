#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <unistd.h>

bool thread_start_flag_ = false;
bool thread_stop_flag_ = false;

void OutputValue()
{
	std::cout << "wait for start thread ! \n";
	int i = 1;
	while(!thread_start_flag_){
		std::cout << i << " secs \n";
		i++;
		sleep(1);
	}

	std::cout << "thread loop \n";
	int j = 1;
	while(true){
		std::cout << j << " secs \n";
		j++;
		sleep(1);
		if (thread_stop_flag_){
			return;
		}
	}
 
}

int main( int argc, char** argv )
{
	std::cout << "main loop\n";
	std::cout << "creat a thread and after 3 secs thread will be start !! \n";
	std::thread mThread1(OutputValue);
	sleep(3);
	thread_start_flag_ = true;
	std::cout << "After 5 secs thread will be stop \n";
	sleep(5);
	thread_stop_flag_ = true;
	if (mThread1.joinable()) {
	  mThread1.join();    
	}

  return 0;
}