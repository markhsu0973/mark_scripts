#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mutex;
std::condition_variable cv;
std::string data;
bool ready = false;  
bool processed = false; 
bool is_worker = false;
void Worker() {
  is_worker = true;
  std::cout << "S2-1" << std::endl;
  std::unique_lock<std::mutex> lock(mutex);

  std::cout << "S2-2" << std::endl;
  cv.wait(lock, [] { return ready; });
  std::cout << "S2-3" << std::endl;

  std::cout << "工作线程正在处理数据..." << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(1));
  data += " 已处理";

  processed = true;
  std::cout << "工作线程通知数据已经处理完毕。" << std::endl;

  lock.unlock();

  cv.notify_one();
  is_worker = false;
} 

int main() {
  // std::thread worker(Worker);

  std::cout << "S1-1" << std::endl;
  {
    // std::lock_guard<std::mutex> lock(mutex);
    std::cout << "主线程正在准备数据..." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(3));
    data = "样本数据";
    ready = true;
    std::cout << "主线程通知数据已经准备完毕。" << std::endl;
  }
  std::cout << "S1-2" << std::endl;
  cv.notify_one();
  std::cout << "S1-3" << std::endl;

  if (is_worker) {
	{
		std::unique_lock<std::mutex> lock(mutex);
		cv.wait(lock, [] { return processed; });
	} 	
  }

  std::cout << "S1-4" << std::endl;
  std::cout << "回到主线程，数据 = " << data << std::endl;

  // worker.join();

  return 0;
}