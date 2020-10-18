#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class AnyString {
	std::string anyString;

public:
	AnyString(const std::string& anyString) : anyString(anyString) {}
	std::string getAnyString() {
		return "Stored String :: " + anyString;
	}friend std::ofstream& operator<<(std::ofstream& o, AnyString& h);
};

std::ofstream& operator<<(std::ofstream& o, AnyString& h) {
  o << h;
  return o;
}

int main() {
	std::ofstream out("testOveroding.txt");
	AnyString a("Hello, this is operator overloading test!!!");
	std::string output = a.getAnyString();
	out << output << std::endl;

	return 0;
}