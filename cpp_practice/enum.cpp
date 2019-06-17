#include <iostream>
using namespace std;

int main(){
    enum days{one, two, three}day;
    day = one;
    cout<<one<<endl;
    switch(day){
        case one:
            cout << "one" << endl;
            break;
        case two:
            cout << "two" << endl;
            break;
        default:
            cout << "three" << endl;
            break;
    }
    return 0;
}
