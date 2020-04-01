#include <iostream>
#include <vector>

using namespace std;

//STL vector的几种清空容器（删除）办法

void test()
{
    vector<int> vecnum;
    vecnum.push_back(1);
    vecnum.push_back(2);
    vecnum.push_back(3);
    vecnum.push_back(4);
    vecnum.push_back(5);
    vecnum.push_back(6);
    vecnum.push_back(7);

    //打印vector的大小和容量
    cout << "old: size = " << vecnum.size() << " ; capacity = " << vecnum.capacity() << endl;

    //1. clear()，清空元素，但不回收空间

    //vecnum.clear();

    //2. 使用 erase循环删除，结果同上

    //vector<int>::iterator it;
    //for (it = vecnum.begin(); it != vecnum.end(); )
    //{
    //    //注意使用erase()方法时，迭代不要随意的++
    //    it = vecnum.erase(it);
    //}

    //结论：erase在每次操作时，迭代器指针会整体前移1，就是每次都会移动全部数据，所以vector不适合做频繁删除的容器

    //3. 最简单的使用swap,清除元素并回收内存
    //3.1 写法一

    vector<int>().swap(vecnum);

    //3.2 写法二
    // vecnum.swap(vector<int>());

    //打印vector的大小和容量
    cout << "last: size = " << vecnum.size() << " ; capacity = " << vecnum.capacity() << endl;
//
    vecnum.push_back(4);
    vecnum.push_back(5);
    vecnum.push_back(6);
    vecnum.push_back(7);
    cout << "last: size = " << vecnum.size() << " ; capacity = " << vecnum.capacity() << endl;

    vector<int>().swap(vecnum);
    cout << "last: size = " << vecnum.size() << " ; capacity = " << vecnum.capacity() << endl;
}

int main()
{
    test();
    getchar();
    return 0;
}