#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

int main() {
	std::string filename = "test.txt";
	std::ifstream file(filename, std::ios::binary);

	if (!file.is_open()) {
		std::cout << "shit is hitting the fan" << std::endl;
		return 1;
	}

	std::vector<unsigned char> buffer((std::istreambuf_iterator<char>)(file), std::istreambuf_iterator<char>());
}