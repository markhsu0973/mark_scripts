#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

#include <unistd.h>

using namespace std;

std::condition_variable cv1_ ;
std::condition_variable cv2_ ;
std::mutex mtx1_ ;
std::mutex mtx2_ ;
bool ready1_ = false ;
bool ready2_ = false ;


void foo(const int& n) {
    for (int i = 0; i < n; i++)
    {
        std::unique_lock<std::mutex> lock1(mtx1_) ;
        while (!ready1_) {
        	cv1_.wait(lock1) ;
        }
        std::cout << "foo function: ";
        std::cout << "The product of 2 by " << i << " is " << 2 * i << std::endl ;
        ready2_ = true ;
        ready1_ = false;
        lock1.unlock() ;
        cv2_.notify_one() ;
    }
}
void OutputValue( int n )
{
    for (int i = 0; i < n; i++)
    {
        std::cout<<"OutputValue fuc i = "<<i<<"\t";
        ready1_ = true ;
        cv1_.notify_one() ;
        std::unique_lock<std::mutex> lock2(mtx1_) ;
        while (!ready2_) {
        	cv2_.wait(lock2) ;
        }
        lock2.unlock() ;
        ready2_ = false ;

    }
}

int main( int argc, char** argv )
{

  cout << "\nCall function with thread" << endl;
  thread mThread1( OutputValue, 30 );
  std::cout << "Call the 2nd function foo\n" ; 
  thread mThread2(foo, 30);

  if (mThread1.joinable()) {
      mThread1.join();    
  }
  if (mThread2.joinable()) {
      mThread2.join();    
  }

  return 0;
}