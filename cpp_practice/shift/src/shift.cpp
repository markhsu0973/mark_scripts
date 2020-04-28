#include <iostream>
#include <vector>

using namespace std;

  enum ReadIndex {
    READ_MIN_FREQUENCY,
    READ_MAX_FREQUENCY,
    READ_ACCEL_TIME,
    READ_LINE_FLEXIBLE,
    READ_NUMBER
  };
  enum PayloadIndex {
    IDX_PAYLOAD_MIN_FREQUENCY_L,
    IDX_PAYLOAD_MIN_FREQUENCY_H,
    IDX_PAYLOAD_MAX_FREQUENCY_L,
    IDX_PAYLOAD_MAX_FREQUENCY_H,
    IDX_PAYLOAD_ACCEL_TIME_L,
    IDX_PAYLOAD_ACCEL_TIME_H,
    IDX_PAYLOAD_LINE_FLEXIBLE,
    IDX_PAYLOAD_NUMBER
  };

void ComputeLoByteHiByte (int value_, std::uint8_t& lo_, std::uint8_t& hi_) {
	lo_ = value_&(0xff);
  	hi_ = (value_>>8) & 0xff;
}

int main(int argc, char** argv) {

	int value, lo, hi;

	std::vector<std::uint16_t> data;
	// data.resize(READ_NUMBER);
	data.push_back(800);
	data.push_back(11200);
	data.push_back(2000);
	data.push_back(1);

	std::vector<std::uint8_t> data_convert;
	data_convert.resize(IDX_PAYLOAD_NUMBER);

  	ComputeLoByteHiByte(data[READ_MIN_FREQUENCY],
              			data_convert[IDX_PAYLOAD_MIN_FREQUENCY_L],
  						data_convert[IDX_PAYLOAD_MIN_FREQUENCY_H]);
  	ComputeLoByteHiByte(data[READ_MAX_FREQUENCY],
              			data_convert[IDX_PAYLOAD_MAX_FREQUENCY_L],
  						data_convert[IDX_PAYLOAD_MAX_FREQUENCY_H]);
  	ComputeLoByteHiByte(data[READ_ACCEL_TIME],
              			data_convert[IDX_PAYLOAD_ACCEL_TIME_L],
  						data_convert[IDX_PAYLOAD_ACCEL_TIME_H]);
  	data_convert[IDX_PAYLOAD_LINE_FLEXIBLE] = data[READ_LINE_FLEXIBLE];


    for (int i = 0; i < data.size(); i++) {
    	printf("i = %d, data= %d\n", i, data[i]);
    }
    cout << "= = =" << endl;
    for (int i = 0; i < data_convert.size(); i++) {
		printf("i = %d, data= %d\n", i, data_convert[i]);
    }
	return 0;
}
