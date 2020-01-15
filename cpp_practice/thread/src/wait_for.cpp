#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <chrono>             // std::chrono::seconds
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable, std::cv_status
#include <unistd.h>
#include <time.h>

std::condition_variable cv;
int timeout ;
int value = 1;
double START_read,END_read,START_main,END_main;

bool check_function() {
	std::cout << "\nin check_function\n";
	if (value == 0) {
		return true;
	}
	else {
		return false;
	}
}
void read_value() {
  START_read = clock();
  std::cout << "=== read_value Start ===\n";
  sleep(timeout);
  std::cout << "=== read_value End ===\n";
  END_read = clock();
  // std::cout << "read_time：" << (END_read - START_read) / CLOCKS_PER_SEC << " S" << std::endl;
  cv.notify_one();
}

int main ()
{
  std::cout << "Input timeout:";
  std::cin >> timeout;
  std::cout << "timeout: " << timeout << "\n";

  std::cout << "=== main Start ===\n";
  std::thread th (read_value);

  std::mutex mtx;
  std::unique_lock<std::mutex> lck(mtx);
  cv.wait_for(lck, std::chrono::seconds(5),[&] {return check_function();});
  // while (cv.wait_for(lck,std::chrono::seconds(1))==std::cv_status::timeout) {
  //   std::cout << '.';
  // }
  std::cout << "=== main End ===" << '\n';

  th.join();
  
  return 0;
}