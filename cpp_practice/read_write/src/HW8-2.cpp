#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
typedef struct {
string cdatetime;
string address;
string district;
string beat;
string grid;
string crimedescr;
string ucr_ncic_code;
string latitude;
string longitude;
} Data;
int main () {
string str;
ifstream ifile;
Data data[7585];
ifile.open("TestData.csv");
if (ifile){
int c = 0;
cout <<"The content on the TestData.csv is ......" << endl;
while (getline (ifile,str)){
stringstream ss(str);
// ss → 每一行資料轉成串流
getline (ss,data[c].cdatetime,',');
getline (ss,data[c].address,',');
getline (ss,data[c].district,',');
getline (ss,data[c].beat,',');
getline (ss,data[c].grid,',');
getline (ss,data[c].crimedescr,',');
getline (ss,data[c].ucr_ncic_code,',');
getline (ss,data[c].latitude,',');
ss>>data[c].longitude;
c++;
}
cout << "Finish reading data from TestData.csv" << endl;
}
else
cout << "Error" <<endl;
ifile.close();
return 0;
}