#include <iostream>
#include <memory>

class A{
public:

    virtual void show() = 0;
};
 
class B:public A{
public:
     
    int j = 20;
    void show()
    {
        std::cout << "B::show() = " << j << std::endl;
    }
     
};

int main()
{
    B b;
    std::shared_ptr<A> p1 (&b);
    p1->show();
    A* aptr = &b;
    aptr->show();
}