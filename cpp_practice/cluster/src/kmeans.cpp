// k-means算法的C++实现

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <fstream>

using namespace std;

#define K 3 // K为簇数
#define N 20 // N为点数
#define D 2 // D为维数

double point[N][D]; // N个D维点
double barycenter_initial[K][D]; // K个D维初始质心位置
double barycenter_before[K][D]; // 记录每次变换前质心的位置
double barycenter_finished[K][D]; // 最终得到的质心位置
double O_Distance[K]; // 记录某点对于各质心的欧几里得距离
int belongWhichBC[N]; // 记录每个点属于哪一个簇
double mid[D]; // 记录中间值

// 初始化数据点（坐标值均在0-100之间）
void CoordinateDistribution(int n, int d) {
	srand((unsigned)time(NULL)); // 保证随机性
	for(int i=0; i<n; i++) {
		for(int j=0; j<d; j++) {
			point[i][j] = rand() % 101;
		}
	}
}

// 初始化质心（坐标值均在0-100之间）
void initBarycenter(int k, int d) {
	for(int i=0; i<k; i++) {
		for(int j=0; j<d; j++) {
			barycenter_initial[i][j] = rand() % 101;
		}
	}
}

int main(int argc, char** argv) {

	// 为N个点随机分配D维坐标
	int n = N, d = D;
	CoordinateDistribution(n, d);

	// 首先输出K, N, D的值
	cout<<"簇数 K = "<<K<<endl<<"点数 N = "<<N<<endl<<"维数 D = "<<D<<endl<<endl;

	// 输出N个坐标点
	cout<<"系统生成的N个点如下："<<endl;
	for(int i=0; i<n; i++) {
		cout<<"第"<<i+1<<"个"<<"\t";
		for(int j=0; j<d; j++) {
			cout<<point[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;

	// 选择K个初始质心
	int k = K;
	initBarycenter(k, d);

	// 输出系统生成的初始质心
	cout<<"系统生成的K个初始质心如下：" <<endl;
	for(int i=0; i<k; i++) {
		cout<<"第"<<i+1<<"个"<<"\t";
		for(int j=0; j<d; j++) {
			cout<<barycenter_initial[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;

	// 将“首次变换前质点”的位置，初始化为initial时的位置
	// 将“最终得到的质点”的位置均初始化为(-1, -1)，使其与首次变换前的位置不相同
	for(int i=0; i<k; i++) {
		for(int j=0; j<d; j++) {
			barycenter_before[i][j] = barycenter_initial[i][j];
			barycenter_finished[i][j] = -1;
		}
	}

	int times = 0; // 定义循环进行到第几次

	// 循环计算
	while(true) {

		for(int i=0; i<n; i++) { // 对于每一个点
			for(int j=0; j<k; j++) { // 求对于K个簇，每个簇的欧氏距离
				double sum = 0;
				for(int x=0; x<d; x++) {
					sum = sum + pow(point[i][x]-barycenter_before[j][x], 2);
				}
				// O_Distance[j] = sqrt(sum); // 因为sum和sqrt(sum)是正相关，所以要比较sqrt(sum)的大小，只需比较sum的大小
				O_Distance[j] = sum;
			}
			int x = 0, temp = x; // temp里面保存的是：某点所对应的欧氏距离最小的簇序号
			while(x<k) {
				if(O_Distance[x] < O_Distance[temp]) {
					temp = x;
					x++;
				}
				else {
					x++;
				}
			}
			belongWhichBC[i] = temp;
		}

		for(int j=0; j<k; j++) {

			// 将a[]内全部元素置0
			for(int i=0; i<d; i++) {
				mid[i] = 0;
			}

			int number = 0; // 计算某簇中共有多少个点
			for(int i=0; i<n; i++) {
				if(belongWhichBC[i] == j) { // 某点所述簇的序号匹配
					number++;
					for(int y=0; y<d; y++) {
						mid[y] = mid[y] + point[i][y];
					}
				}
			}

			for(int y=0; y<d; y++) {
				barycenter_finished[j][y] = mid[y] / number;
			}

		}

		// flag=0，表示barycenter_before与barycenter_finished内元素完全一致，退出循环
		// flag=1，表示二者内元素不完全一致，仍需继续循环
		int flag = 0;
		for(int i=0; i<k; i++) {
			for(int j=0; j<d; j++) {
				if(barycenter_before[i][j] - barycenter_finished[i][j] <= 0.0001) {
					flag = 0;
					continue;
				}
				else {
					flag = 1;
					break;
				}
			}
			if(flag == 0) {
				continue;
			}
			else {
				break;
			}
		}
		if(flag == 0) {
			times++;
			cout<<"第"<<times<<"轮循环后，得到的K个质心如下："<<endl;
			for(int m=0; m<k; m++) {
				cout<<"第"<<m+1<<"个"<<"\t";
				for(int n=0; n<d; n++) {
					cout<<barycenter_finished[m][n]<<"\t";
				}
				cout<<endl;
			}
			break;
		}
		else {
			times++;
			cout<<"第"<<times<<"轮循环后，得到的K个质心如下："<<endl;
			for(int m=0; m<k; m++) {
				cout<<"第"<<m+1<<"个"<<"\t";
				for(int n=0; n<d; n++) {
					cout<<barycenter_finished[m][n]<<"\t";
				}
				cout<<endl;
			}

			// 若要继续循环，则应该把barycenter_finished中的元素作为下一个循环中barycenter_before中的元素
			for(int i=0; i<k; i++) {
				for(int j=0; j<d; j++) {
					barycenter_before[i][j] = barycenter_finished[i][j];
				}
			}
			continue;
		}
	}
	cout<<endl;

	// 输出最终质心位置
	cout<<"经过 k-means 算法，得到各簇的质心如下："<<endl;
	for(int i=0; i<k; i++) {
		cout<<"第"<<i+1<<"个"<<"\t";
		for(int j=0; j<d; j++) {
			cout<<barycenter_finished[i][j]<<"\t";
		}
		cout<<endl;
		cout<<"该簇所包含的点有："<<endl;
		for(int j=0; j<N; j++) {
			if(belongWhichBC[j] == i) {
				cout<<j+1<<"\t";
			}
		}
		cout<<endl;
	}

	return 0;
}
