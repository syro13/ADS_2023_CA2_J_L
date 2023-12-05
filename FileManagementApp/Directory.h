#pragma once
#include <iostream>
#include <string>

using namespace std;

class Directory {
	string name;
	public:
		Directory();
		Directory(string name);
		void setName(string name);
		string getName();
};

Directory::Directory() {
	name = "";
}

Directory::Directory(string name) {
	this->name = name;
}

void Directory::setName(string name) {
	this->name = name;
}

string Directory::getName() {
	return name;
}

