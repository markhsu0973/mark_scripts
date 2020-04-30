#include <iostream>


using namespace std;


union Msg {
    unsigned char AllMsg;
    struct {
        unsigned bit0:1 ;
        unsigned bit1:1 ;
        unsigned bit2:1 ;
        unsigned bit3:1 ;
        unsigned bit4:1 ;
        unsigned bit5:1 ;
        unsigned bit6:1 ;
        unsigned bit7:1 ;
    };
};




int main()
{
    cout << "Bit fields practice! " << endl;


    Msg Message;
    cout << "input:" << endl;
    int input;
    cin >> input ;
    Message.AllMsg = input;
    cout << "Message.AllMsg= " << (int)Message.AllMsg << endl;


    cout << "Message.bit7 : " << Message.bit7 << endl;
    cout << "Message.bit6 : " << Message.bit6 << endl;
    cout << "Message.bit5 : " << Message.bit5 << endl;
    cout << "Message.bit4 : " << Message.bit4 << endl;
    cout << "Message.bit3 : " << Message.bit3 << endl;
    cout << "Message.bit2 : " << Message.bit2 << endl;
    cout << "Message.bit1 : " << Message.bit1 << endl;
    cout << "Message.bit0 : " << Message.bit0 << endl;
    return 0;
}