#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "File.h"

using namespace std;

class Directory {
	string name;
	public:
		Directory();
		Directory(string name);
		void setName(string name);
		string getName();
		void print();
		vector<File*> files;
		void addFile(File* file);
		void removeFile(File* file);
		void removeFile(string name);
		void printFiles();
		int getFilesCount();
		File* getFile(string name);
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

string Directory::getName(){
	return name;
}

void Directory::print() {
	cout << "Directory: " << name << endl;
}

void Directory::addFile(File* file) {
}

void Directory::removeFile(File* file) {
}

void Directory::removeFile(string name) {
}

void Directory::printFiles() {
}

int Directory::getFilesCount() {
	return false;
}

File* Directory::getFile(string name) {
	return nullptr;
}