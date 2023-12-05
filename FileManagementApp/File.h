#pragma once
#include <iostream>
#include <string>
using namespace std;

class File
{
	string name;
	string length;
	string type;
public:
	File();
	File(string name, string length, string type);
	void setName(string name);
	void setLength(string length);
	void setType(string type);
	string getName();
	string getLength();
	string getType();
};

File::File() {
}
File::File(string name, string length, string type) {

}
void File::setName(string name) {

}

void File::setLength(string lenght) {

}

void File::setType(string type) {

}

string File::getName() {
	return false;
}

string File::getLength() {
	return false;
}

string File::getType() {
	return false;
}
