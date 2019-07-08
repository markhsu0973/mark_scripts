#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

#include <unistd.h>

using namespace std;

bool ready1_ = false ;
bool ready2_ = false ;


void foo(const int& n) {

    for (int i = 0; i < n; i++)
    {

        while (!ready1_) {

        }
        std::cout << "foo function: ";
        std::cout << "The product of 2 by " << i << " is " << 2 * i << std::endl ;
        ready2_ = true ;
        ready1_ = false;
    }

    //
}
void OutputValue( int n )
{

    for (int i = 0; i < n; i++)
    {

        cout << "OutputValue: " << i << "\n";

        ready1_ = true ;


        while (!ready2_) {

        }
        ready2_ = false ;

    }
  //

}

int main( int argc, char** argv )
{

  cout << "\nCall function with thread" << endl;
  thread mThread1( OutputValue, 3 );
  std::cout << "Call the 2nd function foo\n" ; 
  thread mThread2(foo, 3);

  if (mThread1.joinable()) {
      mThread1.join();    
  }
  if (mThread2.joinable()) {
      mThread2.join();    
  }

  return 0;
}