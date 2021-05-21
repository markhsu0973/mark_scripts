/**
    Theme: Open File and Read
    Compiler: Dev C++ 4.9.9.2
    Date: 100/05/31
    Author: ShengWen
    Blog: https://cg2010studio.wordpress.com/
*/
#include<iostream>
#include<fstream>
using namespace std;
 
int main(){
    char filename[]="test.csv";
    fstream fp;
    char line[128];
    fp.open(filename, ios::in);//開啟檔案
    if(!fp){//如果開啟檔案失敗，fp為0；成功，fp為非0
        cout<<"Fail to open file: "<<filename<<endl;
    }
    // cout<<"File Descriptor: "<<fp<<endl;

    while(fp.getline(line, sizeof(line), '\n')){
        cout<<line<<endl;//print 每一行
    }
 
    fp.close();//關閉檔案

	return 0 ;
    // system("pause");
    // return EXIT_SUCCESS;
}