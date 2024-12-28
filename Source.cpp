#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <tuple>
#include <map>

typedef std::tuple<int, int, char> LZ77Token;

std::vector<unsigned char> GetFile(std::string filename) {
	std::ifstream file(filename, std::ios::binary);

	if (!file.is_open()) {
		std::cout << "shit is hitting the fan" << std::endl;
	}

	std::vector<unsigned char> buffer((std::istreambuf_iterator<char>)(file), std::istreambuf_iterator<char>());

	file.close();
	return buffer;
}

std::vector<std::pair<char, int>> GetFrequencyPairs(std::vector<unsigned char>& buffer) {
	std::map<char, int> freq;
	for (size_t i = 1; i < buffer.size(); i += 2) {
		short combined = (static_cast<short>(buffer[i - 1]) << 8) | buffer[i];
		freq[combined]++;
	}

	std::vector<std::pair<char, int>> freq_vector;
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
	return freq_vector;
}

std::vector<LZ77Token> Compression(std::vector<unsigned char>& data) {
	int searchBuffer = 16;
	int lookBuffer = 16;
	std::vector<LZ77Token> compressed;
	int position = 0;

	while (position < data.size()) {
		char next = '\0';
		int maxLenght = 0;
		int offset = 0;

		int searchStart = std::max(0, static_cast<int>(position) - searchBuffer);
		int searcheEnd = static_cast<int>(position);

		for (int i = searchStart; i < searcheEnd; ++i) {
			int lenght = 0;
			while (lenght < lookBuffer && position + lenght < data.size() && i + lenght < position && data[i + lenght] == data[position + lenght]) {
				lenght++;
			}
			if (lenght > maxLenght) {
				maxLenght = lenght;
				offset = position - i;
			}
		}

		next = (position + maxLenght < data.size()) ? data[position + maxLenght] : '\0';
		compressed.emplace_back(offset, maxLenght, next);
		position += maxLenght + 1;
	}

	return compressed;
}

void compressedOut(const std::vector<LZ77Token>& compressed) {
	for (const auto& token : compressed) {
		std::cout << std::get<0>(token) << ", " << std::get<1>(token) << ", " << std::get<2>(token) << std::endl;
	}
}

int main() {

	std::vector<unsigned char> buffer{ 'h', 'e', 'o', 'h','e','o'};
	//std::vector<unsigned char> buffer =;
	std::vector<LZ77Token> cheese = Compression(buffer);
	compressedOut(cheese);
	//std::vector<std::pair<char, int>> freq = GetFrequencyPairs(buffer);



	std::string nya;
	std::cin >> nya;
}

void IDontFeel() {
	std::cout << "and i CANT EAT" << " =)" << std::endl;
}