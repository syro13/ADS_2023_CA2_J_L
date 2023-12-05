#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "../Stack/Stack.h"
#include "../Trees/Tree.h"

using namespace std;

template <class T>
class XMLLoader
{
	public:
	T* fileName;
    Tree<T> *fileTree;
	XMLLoader(T& fileName);
	bool load();
    void makeTree();
};

template <class T>
XMLLoader<T>::XMLLoader(T& fileName)
{
	this->fileName = &fileName;
}

template <class T>
bool XMLLoader<T>::load()
{
    MyStack<string> stack;
    string line;
    ifstream myfile(fileName->c_str());

    if (!myfile.is_open())
    { 
        cout << "Unable to open file: " << fileName << endl;
        return false;
    }

    while (getline(myfile, line))
    {
        int openingTag = line.find("<");
        int closingTag = line.find(">");
        if (openingTag != -1 && closingTag != -1) {
            string tag = line.substr(openingTag + 1, closingTag - openingTag - 1);
            cout << "Tag: " << tag << endl;
            if (tag[0] != '/') {
				cout << "Pushing: " << tag << endl;
				stack.push(tag);
			}
            if(closingTag != line.length() - 1)
			{
				string content = line.substr(closingTag + 1, line.length() - closingTag - 1);
                openingTag = content.find("<");
                closingTag = content.find(">");
                if (openingTag != -1 && closingTag != -1) {
					string tag = content.substr(openingTag + 1, closingTag - openingTag - 1);
                    cout << "Tag: " << tag << endl;
                    if (tag[0] == '/' && tag.substr(1, tag.length() -1) == stack.top()) {
                        cout << "Popping: " << tag.substr(1, tag.length() -1) << endl;
                        stack.pop();
                    }
				}
            }
            if (tag[0] == '/' && tag.substr(1, tag.length()) == stack.top()) {
                    cout << "Popping: " << tag.substr(0, tag.length() - 1) << endl;
                    stack.pop();
            }
            //cout << "---------------------------------------------------" << endl;
            //cout << "           tag " << tag << endl;
            //cout << "           tag substring " << tag.substr(0, tag.length()) << endl;
            //cout << "           stack.top() " << stack.top() << endl;
            //cout << "---------------------------------------------------" << endl;
            
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
}