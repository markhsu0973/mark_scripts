#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <chrono>             // std::chrono::seconds
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable, std::cv_status

int value;
bool is_WMsg_sub = false;
bool is_WMsg_main = false;

std::condition_variable cv_WMsg_sub;
std::mutex mtx_WMsg_sub;
std::condition_variable cv_WMsg_main;
std::mutex mtx_WMsg_main;

void read_value() {
  is_WMsg_sub = true;
  if (is_WMsg_main) {
  	std::cout << "wait for in read" << std::endl;
  	std::unique_lock<std::mutex> lck_read(mtx_WMsg_main);
  	cv_WMsg_main.wait_for(lck_read,std::chrono::seconds(1));
  }
  std::cout << "start work in read" << std::endl;  
  
  // std::unique_lock<std::mutex> lck(mtx_WMsg);
  // cv_WMsg.wait_for(lck,std::chrono::seconds(1));
  std::cout << "read value OK!" << std::endl;
  is_WMsg_sub = false;
  std::cout << "notify in read" << std::endl;
  cv_WMsg_sub.notify_one();
}

void run_read_func() {
	for (int i = 0; i < 3; i++) {
		read_value();
		std::this_thread::sleep_for(std::chrono::seconds(1));		
	}

}

int main ()
{
  std::thread th (run_read_func);

  while(1) {
  	is_WMsg_main = true;
  	if (is_WMsg_sub) {
  	  std::cout << "wait for in main" << std::endl;
  	  std::unique_lock<std::mutex> lck_main(mtx_WMsg_sub);
  	  cv_WMsg_sub.wait_for(lck_main,std::chrono::seconds(1));
  	}
  	
  	std::cout << "start work in main" << std::endl;
	std::cout << "main read" << std::endl;
	std::cout << "main write" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	is_WMsg_main = false;
	std::cout << "notify in main" << std::endl;   
	cv_WMsg_main.notify_one();
  }

  th.join();

  return 0;
}
