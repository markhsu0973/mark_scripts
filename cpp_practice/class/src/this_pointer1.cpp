#include <iostream>
 
class Demo {
public:
    Demo(int a, int b) {
        std::cout << "constructor called.." << std::endl;
         
        this->a = a;
        this->b = b;
    }
  
    int do_something() {
        return this->a + this->b;
    }
 
private:
    int a;
    int b;
};
 
int main(void) {
    Demo d(22, 60);
    std::cout << d.do_something() << std::endl;
 
    return 0;
}