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
		vector<File*> files = vector<File*>(); 
		void addFile(File* file);
		void removeFile(File* file);
		void removeFile(string name);
		void printFiles();
		int getFilesCount();
		File* getFile(string name);
		File* getFile(int index);
		string getFilesNames();
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
	cout << "Adding file: " << file->getName() << " to Directory: " << this->name << endl;
	this->files.push_back(file);
	cout << "File count: " << files.size() << endl;
}

void Directory::removeFile(File* file) {
	for (int i = 0; i < files.size(); i++) {
		if (this->files[i] == file) {
			this->files.erase(files.begin() + i);
		}
	}

}

void Directory::removeFile(string name) {
	for (int i = 0; i < files.size(); i++) {
		if (this->files[i]->getName() == name) {
			files.erase(files.begin() + i);
		}
	}

}

void Directory::printFiles() {
	cout << "Files: " << endl;
	for (int i = 0; i < this->files.size(); i++) {
		cout << i << ". " << this->files[i]->getName() << endl;

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
	return nullptr;
}

File* Directory::getFile(int index) {
	return files[index];
}

string Directory::getFilesNames() {
	string names = "";
	vector<File*>::iterator it = files.begin();
	for(it;it<files.end();it++){
		names += (*it)->getName() + "\n";
	}
	return names;
}
