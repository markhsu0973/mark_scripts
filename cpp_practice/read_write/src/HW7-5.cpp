#include<iostream>
#include<stdlib.h>
#include<string>
#include<time.h>
#define PEOPLE 4  //有幾個人
#define USERNUM 13  //每人牌數
using namespace std;

string pflo[4]={"梅花","方塊","愛心","黑桃"};
string pnum[13]={"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

int main(){
        int poker[4][13]={0};  //52張牌是否有重複的依據
        string user[PEOPLE][USERNUM];  //使用者4人 每人有5張牌
        int flo,num,all;  //用來產生亂數
        srand((unsigned)time(NULL));
        for(int i=0;i<4;i++){  //poker設初值(devc++)
                for(int j=0;j<13;j++){
                        poker[ i][j]=0;
                }
        }
        for(int i=0;i<PEOPLE;i++){  //人數
                for(int j=0;j<USERNUM;j++){  //每個人的牌數
                        do{
                                /*
                                flo=(int)rand()%4;
                                num=(int)rand()%13;
                                */
                                all=(int)rand()%52;
                                flo=all/13;
                                num=all%13;
                        }while(poker[flo][num]==1);
                        poker[flo][num]=1;
                        user[ i][j]=pflo[flo]+pnum[num];
                }
        }
        //印出每個人的牌
        for(int i=0;i<PEOPLE;i++){
                cout << "第" << i+1 << "人: ";
                for(int j=0;j<USERNUM;j++)
                        cout << user[ i][j] << "\t";
                cout << endl;
        }
        return 0;
}