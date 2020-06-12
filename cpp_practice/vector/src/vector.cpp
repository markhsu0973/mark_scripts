#include <iostream>
#include <vector>

using namespace std;

//STL vector的几种清空容器（删除）办法

void test_vec(int n) {
	vector<int> vec_temp;
	for (int i = 0; i < n; i++) {
		vec_temp.push_back(i);
	}
	cout << "size = " << vec_temp.size() << endl;
	for (int i = 0; i < vec_temp.size(); i++) {
		printf("%d ", vec_temp[i]);
	}
	cout << endl;
	
	for (auto iter = vec_temp.begin(); iter != vec_temp.end();) {
		if (*iter != 2) {
		  vec_temp.erase(iter);
		} else {
		  break;
		}
	}
	
	cout << "size = " << vec_temp.size() << endl;
	for (int i = 0; i < vec_temp.size(); i++) {
		printf("%d ", vec_temp[i]);
	}
	cout << endl;

	for (int i = 0; i < vec_temp.size(); i++) {
		if (vec_temp[i] == 8) {
			if ((i + 2) >= vec_temp.size()) {
				printf("fail\n");
				break;
			}
			printf("find\n");
			for (auto iter = (vec_temp.begin() + i + 3); iter != vec_temp.end();) {
				vec_temp.erase(iter);
			}
			break;
		}
	}
	cout << "size = " << vec_temp.size() << endl;
	for (int i = 0; i < vec_temp.size(); i++) {
		printf("%d ", vec_temp[i]);
	}
	cout << endl;

}

/*
void test()
{
    vector<int> vecnum;
    //
    vector<int>().swap(vecnum);
    cout << "old: size = " << vecnum.size() << " ; capacity = " << vecnum.capacity() << endl;
    //
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
*/

int main()
{
    // test();
    test_vec(10);
//    test_vec(5);
//    test_vec(4);
    return 0;
}