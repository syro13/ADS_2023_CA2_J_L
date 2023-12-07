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
	files.push_back(file);
}

void Directory::removeFile(File* file) {
	for (int i = 0; i < files.size(); i++) {
		if (files[i] == file) {
			files.erase(files.begin() + i);
		}
	}

}

void Directory::removeFile(string name) {
	for (int i = 0; i < files.size(); i++) {
		if (files[i]->getName() == name) {
			files.erase(files.begin() + i);
		}
	}

}

void Directory::printFiles() {
	for (int i = 0; i < files.size(); i++) {
		cout << "File: " << files[i]->getName() << endl;
	}
}

int Directory::getFilesCount() {
	return files.size();
}

File* Directory::getFile(string name) {
	for (int i = 0; i < files.size(); i++) {
		if (files[i]->getName() == name) {
			return files[i];
		}
	}
	return NULL;
}