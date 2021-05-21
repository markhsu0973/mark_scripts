#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;

 int main()
 {
 	double sigma;
	srand( (unsigned) time(NULL) );
	int M, N, total_front_side_time = 0;
	cout << "Please enter the times(M). and the amount of the coins(N): " << endl;
	cin >> M >> N;
	for (int i = 1; i <= N; i++) {
		double probability_this_time;
		int front_side_time = 0, back_side_time = 0;
		for(int j = 0; j < M; j++) {
			int side = rand() % 2;
			// cout << side <<endl;
			if (side) {
				back_side_time ++;
			}
			else {
				front_side_time ++;
			}
		}
		total_front_side_time = total_front_side_time + front_side_time;
		cout << i << " front side= " << front_side_time << "times" << endl;
	}
	cout << "==========" << endl;
	cout << "total_front_side_time" << total_front_side_time << endl;
	double probability = (double)total_front_side_time / (M * N);
	cout << "probability: " << probability << endl;	
	sigma = sqrt(M * N * probability * (double)(1 - probability));
	cout << "1-th sigma: " << sigma << endl;
	cout << "2-th sigma: " << 2 * sigma << endl;
	cout << "3-th sigma: " << 3 * sigma << endl;
	return 0;
 }

