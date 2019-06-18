#include <iostream>
#include <thread>
#include <unistd.h>
void thread_function_1()
{
    for (int i = 0; i < 5; i++)
    {
        std::cout<<"thread function1 "<< i <<std::endl;
        sleep(5);
    }
}
void thread_function_2()
{
    for (int i = 0; i < 5; i++)
    {
        std::cout<<"thread function2 "<< i <<std::endl;
        sleep(3);
    }
}
 
int main()  
{
    std::cout<<"It's thread practice code !!!"<<std::endl;
    std::thread thread1(thread_function_1);
    std::thread thread2(thread_function_2);
    for (int i = 0; i < 5; i++)
    {
        std::cout<<"main function "<< i <<std::endl;
        sleep(1);
    }
    thread1.join();
    thread2.join();     
    std::cout<<"Exit of Main function"<<std::endl;
    return 0;
}