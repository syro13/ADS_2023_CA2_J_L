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

// Class for loading and processing XML files into a tree structure
template <class T>
class XMLLoader
{
public:
    string fileName;
    Tree<Directory>* fileTree;

    // Constructor to initialize the XMLLoader with a file name
    XMLLoader(string fileName);

    // Getter for the file name
    string getFileName() { return fileName; }

    // Setter for the file name
    void setFileName(string fileName) { this->fileName = fileName; }

    // Load function to parse the XML file and check for validity
    bool load();

    // Function to create a tree structure based on the XML file content
    void makeTree();
};

// Constructor implementation
template <class T>
XMLLoader<T>::XMLLoader(string fileName)
{
    this->fileName = fileName;
    fileTree = nullptr;
}

// Load function implementation
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
        if (openingTag != -1 && closingTag != -1)
        {
            string tag = line.substr(openingTag + 1, closingTag - openingTag - 1);
            if (tag[0] != '/')
            {
                stack.push(tag);
            }
            if (closingTag != line.length() - 1)
            {
                string content = line.substr(closingTag + 1, line.length() - closingTag - 1);
                openingTag = content.find("<");
                closingTag = content.find(">");
                if (openingTag != -1 && closingTag != -1)
                {
                    string tag = content.substr(openingTag + 1, closingTag - openingTag - 1);
                    if (tag[0] == '/' && tag.substr(1, tag.length() - 1) == stack.top())
                    {
                        stack.pop();
                    }
                }
            }
            if (tag[0] == '/' && tag.substr(1, tag.length()) == stack.top())
            {
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

// makeTree function implementation
template <class T>
void XMLLoader<T>::makeTree()
{
    TreeIterator<Directory> iter(fileTree);
    File* file = nullptr;
    string prevTag;
    string line;
    ifstream myfile(fileName);

    while (getline(myfile, line))
    {
        int openingTag = line.find("<");
        int closingTag = line.find(">");
        if (openingTag != -1 && closingTag != -1)
        {
            string tag = line.substr(openingTag + 1, closingTag - openingTag - 1);
            if (tag == "dir")
            {
                prevTag = tag;
            }
            if (tag == "file")
            {
                prevTag = tag;
                file = new File("", "", "");
            }
            if (tag == "name" && prevTag == "dir")
            {
                string content = line.substr(closingTag + 1, line.length() - closingTag - 1);
                int openingTag = content.find("<");
                string name = content.substr(0, openingTag);
                Directory dir(name);
                if (iter.node == nullptr)
                {
                    fileTree = iter.node = new Tree<Directory>(dir);
                    iter.resetIterator();
                }
                else
                {
                    iter.appendChild(dir);
                    iter.childEnd();
                    iter.down();
                }
                prevTag = tag;
            }
            if (tag == "name" && prevTag == "file")
            {
                string content = line.substr(closingTag + 1, line.length() - closingTag - 1);
                int openingTag = content.find("<");
                string name = content.substr(0, openingTag);
                file->setName(name);
            }
            if (tag == "length" && prevTag == "file")
            {
                string content = line.substr(closingTag + 1, line.length() - closingTag - 1);
                int openingTag = content.find("<");
                string length = content.substr(0, openingTag);
                file->setLength(length);
            }
            if (tag == "type" && prevTag == "file")
            {
                string content = line.substr(closingTag + 1, line.length() - closingTag - 1);
                int openingTag = content.find("<");
                string type = content.substr(0, openingTag);
                file->setType(type);
            }
            if (tag == "/file")
            {
                iter.addToVector(file);
                prevTag = tag;
                file = nullptr;
            }
            if (tag == "/dir")
            {
                iter.up();
            }
        }
    }
}
