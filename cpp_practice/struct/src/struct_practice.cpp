// example: one class, two objects
#include <iostream>

using namespace std;
typedef unsigned char CommandEntity;

typedef union _SensorStatus {
struct {
  unsigned char detect_plate_start : 1;
  unsigned char detect_plate_end : 1;
  unsigned char detect_plate_pressed : 1;
  unsigned char detect_roller_in : 1;
  unsigned char detect_roller_out : 1;
  unsigned char button_start_1 : 1;
  unsigned char button_start_2 : 1;
  unsigned char button_forced : 1;
};
CommandEntity byte;
} SensorStatus;


int main () {
	SensorStatus bit_data_;
	bit_data_.byte = 0x00;
	if (bit_data_.button_start_1 == 1) {
		cout << "bit_data_.button_start_1 == 1" << endl;
	}
	cout << "bit_data_.button_start_1: " << unsigned(bit_data_.button_start_1) << endl;
  return 0;
}
