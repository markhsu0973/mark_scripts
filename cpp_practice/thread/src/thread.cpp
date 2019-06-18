#include <iostream>
#include <thread>
#include <unistd.h>
void thread_function()
{

    std::cout<<"thread function "<<std::endl;

}
 
int main()  
{
    std::cout<<"It's thread practice code !!!"<<std::endl;
    std::thread thread1(thread_function);

    std::cout<<"main function "<<std::endl;

    thread1.join();    
    std::cout<<"Exit of Main function"<<std::endl;
    return 0;
}