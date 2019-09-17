#include </home/mark/mark_scripts/cpp_practice/test_include/include/test_include/test_include_main.h>

namespace IncludeMain {

	void TestIncludeMain::show() {
		std::cout<<"hello\n";
	}
	double TestIncludeMain::add(double x, double y) {
		double z = x + y;
		std::cout << x << " + " << y << " = " << z << "\n";
	}

} /* End of namespace */

int main( int argc, char** argv )
{
	std::cout << "test include main \n";
	IncludeMain::TestIncludeMain A;
	A.show();
	A.add(1.0, 5.0);
  return 0;
}