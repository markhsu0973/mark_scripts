#include </home/mark/mark_scripts/cpp_practice/test_include/include/test_include/test_include_main.h>
#include<memory>
int main( int argc, char** argv )
{
	std::cout << "test include sub\n";
	std::unique_ptr<IncludeMain::TestIncludeMain> hpDriver_ ;
	hpDriver_.show();
	IncludeMain::TestIncludeMain A;
	// A.show();
	// A.add(1.0, 5.0);
  return 0;
}