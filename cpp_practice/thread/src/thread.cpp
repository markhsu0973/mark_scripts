#include <iostream>
#include <thread>

using namespace std;

void test_func2( int i )
{
  cout << i << endl;
}

int main( int argc, char** argv )
{
  thread mThread( test_func2, 23 );
  mThread.join();

  return 0;
}