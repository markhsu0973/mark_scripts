#include <iostream>
#include <fstream>
using namespace std;

void convertToASCII(string letter)
{   
    int space_cnt = 0;
    for (int i = 0; i < letter.length(); i++)
    {
        space_cnt++;
        if (letter[i] == ' ') {
            int num = 0;
            if (space_cnt = 3) {
                num = num + letter[i];
                num = num + (10 * letter[i-1]);
                num = num + (100 * letter[i-2]);
            }
            if (space_cnt = 2) {
                num = num + letter[i];
                num = num + (10 * letter[i-1]);
            }
            if (space_cnt = 1) {
                num = num + letter[i];
            }
            cout << "num=" << num << endl;
            space_cnt = 0;
        }
        // char x = letter.at(i);
        // char x = (char)letter[i];
        // cout << x;
        // cout << int(x);
        // cout << int(x) << endl;
    }
    // cout << "\n";
}
//https://www.geeksforgeeks.org/convert-the-ascii-value-sentence-to-its-equivalent-string/
void asciiToSentence(string str, int len) 
{ 
    int num = 0; 
    for (int i = 0; i < len; i++) { 
  
        // Append the current digit 
        num = num * 10 + (str[i] - '0'); 
        cout << "str[" << i << "] = " << str[i] << endl;
        // If num is within the required range 
        if (num >= 32 && num <= 122) { 
  
            // Convert num to char 
            char ch = (char)num; 
            // cout << ch; 
  
            // Reset num to 0 
            num = 0; 
        } 
    } 
    cout << "\n";
} 

int main () {
	bool first_time = true;
    string str, str2, str3;
    ifstream ifile;

    ifile.open("HW7_4_Encoded.txt");
    if (ifile)
    {
        while (getline (ifile,str) ){
            // cout << str << endl;
            // int len = str.length();
            // asciiToSentence(str, len);

            convertToASCII(str);
        }
    }
    else
    {
        cout << "Error" <<endl;
    }
    ifile.close();

	// ofstream file;
 //    file.open("HW7_2.txt");
 //    if (file)
 //    {
 //            file << str2;
 //    }
 //    else
 //    {
 //        cout << "Error" <<endl;
 //    }

 //    file.close();


    return 0;
}


