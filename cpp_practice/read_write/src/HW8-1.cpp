#include <iostream>

using namespace std;

enum WeekDay{
	Mon = 1,
	Tue,
	Wed,
	Thu,
	Fri,
	Sat,
	Sun
};

int main () {
    WeekDay week_day;
    int N;
    cout << "Please enter the week day: " << endl;
    cin >> N;
    if ( 1 <= N && N <=7) {
		switch(N){
			case Mon:
				cout << "Monday" << endl;
				break;
			case Tue:
				cout << "Tuesday" << endl;
				break;
			case Wed:
				cout << "Wednesday" << endl;
				break;
			case Thu:
				cout << "Thursday" << endl;
				break;
			case Fri:
				cout << "Friday" << endl;
				break;
			case Sat:
				cout << "Saturday" << endl;
				break;
			case Sun:
				cout << "Sunday" << endl;
				break;
			}
    }
    else {
    	cout << "Input Error" << endl;
    }
    return 0;
}

