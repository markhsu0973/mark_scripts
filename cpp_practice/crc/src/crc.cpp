#include <iostream>           // std::cout
#include <vector>
#include <array>
int main ()
{
	std::cout << "practice calculate CRC" << std::endl;
	std::array<uint8_t, 9> msg = {245, 01, 170, 01, 00, 01, 244, 166, 45};
	unsigned char tmp[msg.size()];
	int size = 0;

	for(std::vector<uint8_t>::const_iterator it = msg.begin(); it!= msg.end(); ++it){
		tmp[size] = *it;
		size++;
	}
	return 0;
}
