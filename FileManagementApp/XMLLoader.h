#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "../Stack/Stack.h"
#include "../Trees/Tree.h"
#include "../Trees/TreeIterator.h"
#include "File.h"
#include "Directory.h"
#include "TreeNode.h"

using namespace std;

template <class T>
class XMLLoader
{
	public:
	string fileName;
    Tree<Directory> *fileTree;
	XMLLoader(string fileName);
    string getFileName() { return fileName; }
    void setFileName(string fileName) { this->fileName = fileName; }
	bool load();
    void makeTree();
};

template <class T>
XMLLoader<T>::XMLLoader(string fileName)
{
	this->fileName = fileName;
    Directory root("Root");
    fileTree = new Tree<Directory>(root);
}

template <class T>
bool XMLLoader<T>::load()
{
    MyStack<string> stack;
    string line;
    ifstream myfile(fileName);

    if (!myfile.is_open())
    { 
        cout << "Unable to open file: " << fileName << endl;
        return false;
    }

    while (getline(myfile, line))
    {
        size_t openingTag = line.find("<");
        size_t closingTag = line.find(">");
        if (openingTag != -1 && closingTag != -1) {
            string tag = line.substr(openingTag + 1, closingTag - openingTag - 1);
            if (tag[0] != '/') {
				stack.push(tag);
			}
            if(closingTag != line.length() - 1)
			{ 
				string content = line.substr(closingTag + 1, line.length() - closingTag - 1);
                openingTag = content.find("<");
                closingTag = content.find(">");
                if (openingTag != -1 && closingTag != -1) {
					string tag = content.substr(openingTag + 1, closingTag - openingTag - 1);
                    if (tag[0] == '/' && tag.substr(1, tag.length() -1) == stack.top()) {
                        stack.pop();
                    }
				}
            }
            if (tag[0] == '/' && tag.substr(1, tag.length()) == stack.top()) {
                    stack.pop();
            }
            
        }
        
    }

    myfile.close();

    if (stack.isEmpty())
    {
        cout << "XML is valid" << endl;
        return true;
    }
    else
    {
        stack.print();
        cout << "Error: Mismatched tags in XML" << endl;
        return false;
    }
}

template <class T>
void XMLLoader<T>::makeTree() {
    /*TreeIterator* iter = new TreeIterator(fileTree);
    Directory* currentDir = nullptr;
    File* currentFile = nullptr;
    string line;
    string prevTag;
    ifstream myfile(fileName);

    if (!myfile.is_open())
    {
		cout << "Unable to open file: " << fileName << endl;
		return;
	}

    while (getline(myfile, line)) {
        size_t openingTag = line.find("<");
		size_t closingTag = line.find(">");
        if (openingTag != -1 && closingTag != -1) {
			string tag = line.substr(openingTag + 1, closingTag - openingTag - 1);
            cout << "Tag: " << tag << endl;
            if (tag == "dir") {
                prevTag = tag;
                cout << "prevTag: " << prevTag << endl;
                currentDir = new Directory();
                iter->appendChild(currentDir);
                iter->childForth();
                iter->down();
            }
            else if (tag == "file") {
                prevTag = tag;
                cout << "prevTag: " << prevTag << endl;
                currentFile = new File();
                iter->appendChild(currentFile);
                iter->childForth();
                iter->down();
            }
            else if (tag == "name" && currentDir != nullptr && prevTag == "dir") {
                string content = line.substr(closingTag + 1, line.length() - closingTag - 1);
                currentDir->setName(content);
                cout << "name: " << content << endl;
            }
            else if (tag == "name" && prevTag == "file") {
                string content = line.substr(closingTag + 1, line.length() - closingTag - 1);
                currentFile->setName(content);
                cout << "name: " << content << endl;
            }
            else if (tag == "length" && prevTag == "file") {
                string content = line.substr(closingTag + 1, line.length() - closingTag - 1);
                currentFile->setLength(content);
                cout << "length: " << content << endl;
            }
            else if (tag == "type" && prevTag == "file") {
                string content = line.substr(closingTag + 1, line.length() - closingTag - 1);
                currentFile->setType(content);
                cout << "type: " << content << endl;
            }
            else if(tag == "/dir" || tag == "/file") {
				iter->up();
				iter->childForth();
			}
        }
    }
    */
}