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
    std::thread threadObj(thread_function);
    for (int i = 0; i < 5; i++)
    {
        std::cout<<"main function "<< i <<std::endl;
        sleep(2);
    }
    threadObj.join();    
    std::cout<<"Exit of Main function"<<std::endl;
    return 0;
}