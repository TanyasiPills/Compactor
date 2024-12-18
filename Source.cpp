#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

int main() {
	std::string filename = "sad.png";
	std::ifstream file(filename, std::ios::binary);

	if (!file.is_open()) {
		std::cout << "shit is hitting the fan" << std::endl;
		return 1;
	}

	std::vector<unsigned char> buffer((std::istreambuf_iterator<char>)(file), std::istreambuf_iterator<char>());

	file.close();

	for (unsigned char byte : buffer) {
		std::bitset<8> bits(byte);
		std::cout << bits << " ";
	}
	std::cout << std::endl;

	std::string nya;

	std::cin >> nya;
}