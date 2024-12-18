#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <map>

std::vector<unsigned char> GetFile(std::string filename) {
	std::ifstream file(filename, std::ios::binary);

	if (!file.is_open()) {
		std::cout << "shit is hitting the fan" << std::endl;
	}

	std::vector<unsigned char> buffer((std::istreambuf_iterator<char>)(file), std::istreambuf_iterator<char>());

	file.close();
	return buffer;
}

int main() {

	std::vector<unsigned char> buffer = GetFile("sad.png");
	
	std::map<uint16_t, int> freq;
	for (size_t i = 1; i < buffer.size(); i += 2) {
		uint16_t combined = (static_cast<uint16_t>(buffer[i - 1]) << 8) | buffer[i];
		freq[combined]++;
	}

	std::vector<std::pair<uint16_t, int>> freq_vector;
	for (const auto& entry : freq) {
		freq_vector.push_back(entry);
	}

	for (size_t i = 0; i < freq_vector.size(); ++i) {
		for (size_t j = i + 1; j < freq_vector.size(); ++j) {
			if (freq_vector[i].second < freq_vector[j].second) {
				std::swap(freq_vector[i], freq_vector[j]);
			}
		}
	}

	std::cout << "Top 16 most common bytes:" << std::endl;
	for (size_t i = 0; i < 16 && i < freq_vector.size(); ++i) {
		uint16_t byte = freq_vector[i].first;
		int count = freq_vector[i].second;
		std::bitset<16> bits(byte);
		std::cout << "Byte: " << bits << " (0x" << std::hex << (int)byte << std::dec << "), Count: " << count << std::endl;
	}

	std::string nya;
	std::cin >> nya;
}