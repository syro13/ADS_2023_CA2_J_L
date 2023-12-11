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

void printTree(Tree<Directory>* tree) {
	TreeIterator<Directory> iterator(tree);
	if (iterator.childValid()) {
		while (iterator.childValid()) {
			Directory directory = iterator.childItem();
			directory.print();
			cout << "files: " << endl;
			directory.printFiles();
			iterator.childForth();
		}
	}
	else {
		cout << "No children" << endl;
	}
}

void displayTree(TreeIterator<Directory> iter, string indent) {
	cout << iter.getNodeInfo() << endl;
	if (iter.childValid())
	{
		cout << "(" << endl;

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

void printTreeStructure(TreeIterator<Directory> iter)
{
	cout << iter.getNodeInfo() << endl;
	iter.childForth();
	while (!iter.childValid())
	{
		printTreeStructure(iter);
		iter.childForth();
	}
	iter.childBack();
}

int main()
{ 
	vector<File*> files = vector<File*>();
	string filename = "test.xml";
	XMLLoader<string> xmlfile(filename);
	bool result = xmlfile.load();
	cout << "result: " << result << endl;
	xmlfile.makeTree();
	TreeIterator<Directory> iter2(xmlfile.fileTree);
	//xmlfile.printTreeStructure(iter);
	//xmlfile.printFiles(iter);
	/*Tree<Directory>* root = new Tree<Directory>(Directory("root"));
	TreeIterator<Directory> iter(root);
	iter.appendChild(Directory("dir1"));
	iter.childForth();
	iter.down();
	iter.down();
	iter.appendChild(Directory("dir2"));
	iter.childForth();
	iter.down(); 
	iter.item().addFile(new File("testN", "testL", "testT"));
	iter.item().addFile(new File("testN2", "testL2", "testT2"));
	iter.appendChild(Directory("dir3"));
	iter.appendChild(Directory("dir4"));
	iter.childForth();
	iter.down();
	iter.appendChild(Directory("dir5"));
	iter.appendChild(Directory("dir6"));
	iter.root();
	files.push_back(new File("testN3", "testL3", "testT3"));*/
	//displayTree(iter, "");
	displayTree(iter2, "");
	//printTree(root);
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
