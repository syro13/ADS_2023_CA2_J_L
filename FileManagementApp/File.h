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
	name = "";
	length = "";
	type = "";
}
File::File(string name, string length, string type) {
	this->name = name;
	this->length = length;
	this->type = type;
}
void File::setName(string name) {
	this->name = name;
}

void File::setLength(string length) {
	this->length = length;
}

void File::setType(string type) {
	this->type = type;
}

string File::getName() {
	return this->name;
}

string File::getLength() {
	return this->length;
}

string File::getType() {
	return this->type;
}
