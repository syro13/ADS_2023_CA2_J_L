// FileManagementApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "XMLLoader.h"
#include "../Trees/Tree.h"
#include "../Trees/TreeIterator.h"
#include "Directory.h"
#include "File.h"


using namespace std;

void displayTree(TreeIterator<Directory> iter, string indent) {
	cout << indent << iter.getNodeInfo(indent) << endl;
	if (iter.childValid())
	{
		cout << indent << "(" << endl;

		while (iter.childValid())
		{
			TreeIterator<Directory> iter2(iter.childIter.currentNode->data);
			displayTree(iter2, "\t" + indent);
			iter.childForth();
		}
		cout << indent << ")";
	}
	cout << endl;
}

int main()
{ 
	bool appOn = true;
	vector<File*> files = vector<File*>();
	string filename = "test.xml";
	XMLLoader<string> xmlfile(filename);
	bool result = xmlfile.load();
	xmlfile.makeTree();
	TreeIterator<Directory> iter2(xmlfile.fileTree);
	displayTree(iter2, "");
	while (appOn) {
		int choice = 0;
		cout << "----------------------------------" << endl;
		cout << "1. Display the tree" << endl;
		cout << "2. Display the files in a directory" << endl;
		cout << "3. Display the files in a directory and its subdirectories" << endl;
		cout << "4. Exit" << endl;
		cout << "----------------------------------" << endl;
		cin >> choice;
		switch (choice) {
		case 1: {
			TreeIterator<Directory> iter(xmlfile.fileTree);
			displayTree(iter, "");
			break;
		}
		case 2: {
			string dirName;
			cout << "Enter the name of the directory: ";
			cin >> dirName;
			TreeIterator<Directory> iter(xmlfile.fileTree);
			if (iter.childValid())
			{
				while (iter.childValid())
				{
					TreeIterator<Directory> iter2(iter.childIter.currentNode->data);
					cout << "*" << iter2.item().getName() << "*" << endl;
					cout << "*" << dirName << "*" << endl;
					if (iter2.item().getName() == dirName) {
						cout << "yes" << endl;
						break;
					}
					else {
						cout << "no" << endl;
					}
					iter.childForth();
				}
			}
			cout << endl;
			break;
		}
		case 3: {
			break;
		}
		case 4: {
			appOn = false;
			break;
		}
		}
	}
}
