#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

#include <unistd.h>

using namespace std;
// thread mThread2;
std::condition_variable cv_ ;
std::mutex mtx_ ;
bool ready_ = false ;


void foo(const int& n) {
	std::cout << "Start executing foo!!\n" ;
	// Wait until another function finishes
	std::unique_lock<std::mutex> lock(mtx_) ;
	while (!ready_) {
		cv_.wait(lock) ;
	}
	std::cout << "I was notified and stopped waiting !!\n" ;
	std::cout << "Set ready to its origianl state i.e. false\n" ;
	ready_ = false ;
	lock.unlock() ;
	std::cout << "Unlock\n" ;

	for (int i = 0 ; i < n ; i++) {
		std::cout << "The product of 2 by " << i << " is " << 2 * i << std::endl ;
	}
}
void OutputValue( int n )
{
  
  cout << "Number:";
  for( int i = 0; i < n; ++ i )
  {
    this_thread::sleep_for( chrono::duration<int, std::milli>( 5 ) );
    cout << " " << i;
  }

  cout << "\nfinish "<<endl;

  std::lock_guard<std::mutex> lock(mtx_) ;
  ready_ = true ;
  std::cout << "I am freed!!\n" ;
  cv_.notify_one() ;
  std::cout << "Notified!!\n" ;
}

int main( int argc, char** argv )
{

  cout << "\nCall function with thread" << endl;
  thread mThread1( OutputValue, 3 );
  std::cout << "Call the 2nd function foo\n" ; 
  thread mThread2(foo, 2);

  if (mThread1.joinable()) {
  	mThread1.join();	
  }
  if (mThread2.joinable()) {
  	mThread2.join();	
  }

  return 0;
}