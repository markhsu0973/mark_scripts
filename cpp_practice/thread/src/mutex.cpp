// g++ std-mutex.cpp -o a.out -std=c++11 -pthread
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

std::mutex g_mutex;
int g_count = 0;

int print2(int n, char c) {
    // critical section (exclusive access to std::cout signaled by locking mtx):
    std::cout << "start print 2" << std::endl;
    std::lock_guard<std::mutex> lock(g_mutex);
    //g_mutex.lock();
    for (int i = 0; i < n; ++i) {
        std::cout << c;
        g_count++;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << '\n';

    std::cout << "count=" << g_count << std::endl;
    //g_mutex.unlock();
    std::cout << "end print 2" << std::endl;
}

int print1(int n, char c) {
    // critical section (exclusive access to std::cout signaled by locking mtx):
    std::cout << "start print 1" << std::endl;
    std::lock_guard<std::mutex> lock(g_mutex);
    //g_mutex.lock();
    for (int i = 0; i < n; ++i) {
        std::cout << c;
        g_count++;
    }
    std::cout << '\n';

    std::cout << "count=" << g_count << std::endl;
    //g_mutex.unlock();
    std::cout << "end print 1" << std::endl;
}

int main() {
    std::thread t1(print1, 10, 'A');
    std::thread t2(print2, 5, 'B');
    t1.join();
    t2.join();

    return 0;
}
