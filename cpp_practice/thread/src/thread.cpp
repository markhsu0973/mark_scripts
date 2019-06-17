#include <iostream>
#include <thread>
#include <unistd.h>
void thread_function()
{
    for (int i = 0; i < 5; i++)
    {
        std::cout<<"thread function "<< i <<std::endl;
        sleep(5);
    }
}
 
int main()  
{
    std::cout<<"It's thread practice code !!!"<<std::endl;
    std::thread thread1(thread_function);
    for (int i = 0; i < 5; i++)
    {
        std::cout<<"main function "<< i <<std::endl;
        sleep(2);
    }
    thread1.join();    
    std::cout<<"Exit of Main function"<<std::endl;
    return 0;
}