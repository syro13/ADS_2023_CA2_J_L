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
}

Directory::Directory(string name) {
}

void Directory::setName(string name) {
}

string Directory::getName() {
	return false;
}