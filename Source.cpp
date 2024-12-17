#include<bitset>
#include<iostream>

int main() {
	int n = 345;
	std::bitset<64> bits(n);
	std::cout << bits << std::endl;
	std::string nm;
	std::cin >> n;
}