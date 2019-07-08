#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex

volatile int counter(0); // non-atomic counter
std::mutex mtx_;           // locks access to counter

void attempt_10k_increases() {
	mtx_.lock();

    for (int i=0; i<10; ++i) {
        ++counter;        
    }
    std::cout << "count: " << counter << "\n";
    mtx_.unlock();
}

int main (int argc, const char* argv[]) {
    std::thread threads[10];
    for (int i=0; i<10; ++i)
        threads[i] = std::thread(attempt_10k_increases);

    for (auto& th : threads) th.join();
    std::cout << counter << " successful increases of the counter.\n";

    return 0;
}