#include <iostream>
#include <thread>

using namespace std;

class funcObj
{
public:
  int iData;
  // std::cout << "class: declare iData\n";
  funcObj()
  {
    iData = 0;
    std::cout << "class: init iData\n";
  }

  void operator()()
  {
  	std::cout << "class: iData is"<<iData<<"\n";
    ++iData;
    std::cout << "class: iData add 1\n";
    std::cout << "class: iData is"<<iData<<"\n";
  }
};

int main( int argc, char** argv )
{
  funcObj co;

  // copy
  std::cout << "start thread 1\n";
  thread mThread1( co );
  std::cout << "thread 1 using copy\n";
  mThread1.join();
  cout << co.iData << endl;

  // reference
  std::cout << "start thread 1\n";
  thread mThread2( ref( co ) );
  std::cout << "thread 2 using copy\n";
  mThread2.join();
  cout << co.iData << endl;

  return 0;
}