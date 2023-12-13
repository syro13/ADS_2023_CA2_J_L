#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include "XMLLoader.h"
#include "../Trees/Tree.h"
#include "../Trees/TreeIterator.h"
#include "Directory.h"
#include "File.h"

using namespace std;

// Function to display the tree structure recursively
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

// Function to print the tree structure using Depth First Search
void printDFS(TreeIterator<Directory> iter)
{
	while (iter.childValid())
	{
		TreeIterator<Directory> iter2(iter.childIter.currentNode->data);
		printDFS(iter2);
		iter.childForth();
	}
	cout << iter.getNodeInfo("") << ", ";
}

// Function to prune empty directories from the tree
void prune(TreeIterator<Directory> iter)
{
	while (iter.childValid())
	{
		TreeIterator<Directory> iter2(iter);
		iter2.down();
		prune(iter2);
		cout << iter.childValid() << endl;
		DListIterator<Tree<Directory>*> iter3 = iter.childIter.currentNode->data->children->getIterator();
		if (!iter3.isValid() && iter.childItem().getFilesCount() == 0)
		{
			iter.removeChild();
		}
		else
		{
			iter.childForth();
		}
	}
}

// Function to get the path of a file in the tree
string getPath(TreeIterator<Directory> iter, string path, string fileName) {
	while (iter.childValid())
	{
		TreeIterator<Directory> iter2(iter.childIter.currentNode->data);
		path = getPath(iter2, path, fileName);
		iter.childForth();
	}
	if (iter.item().getFilesNames().find(fileName) != string::npos || iter.item().getName().find(fileName) != string::npos) {
		Tree<Directory>* temp = iter.node;
		while (temp->parent != nullptr) {
			path = temp->data.getName() + "/" + path;
			temp = temp->parent;
		}
		if (iter.item().getFilesNames().find(fileName) != string::npos) {
			path += iter.item().getFile(fileName)->getName();
		}
		path += "\n";
		return path;
	}
	return path;
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

	while (appOn) {
		int choice = 0;
		cout << "----------------------------------" << endl;
		cout << "1. Display the tree" << endl;
		cout << "2. Count the amount of files within a directory" << endl;
		cout << "3. Display the files in a directory and total memory used" << endl;
		cout << "4. Prune directories" << endl;
		cout << "5. Print path to file" << endl;
		cout << "6. Display the contents of a folder" << endl;
		cout << "7. Exit" << endl;
		cout << "----------------------------------" << endl;
		cin >> choice;

		if (choice < 1 || choice > 7) {
			cout << "Invalid choice" << endl;
			continue;
		}

		try
		{
			switch (choice) {
			case 1: {
				TreeIterator<Directory> iter(xmlfile.fileTree);
				displayTree(iter, "");
				break;
			}
			case 2: {
				string dirName;
				int count = 0;
				cout << "Enter the name of the directory: ";
				cin >> dirName;
				queue<Tree<Directory>*> queue;
				queue.push(xmlfile.fileTree);
				while (!queue.empty())
				{
					DListIterator<Tree<Directory>*> iter = queue.front()->children->getIterator();
					while (iter.isValid())
					{
						queue.push(iter.item());
						iter.advance();
					}
					if (queue.front()->data.getName() == dirName) {
						TreeIterator<Directory> iter(queue.front());
						cout << iter.getNodeInfo("") << endl;
						count += queue.front()->data.getFilesCount();
						if (iter.childValid()) {
							iter.down();
							while (iter.childValid()) {
								cout << iter.getNodeInfo("\t") << endl;
								count++;
								count += iter.item().getFilesCount();
								iter.down();
							}
						}
					}
					queue.pop();
				}
				cout << "Total files & folders: " << count << endl;
				break;
			}
			case 3: {
				string dirName;
				cout << "Enter the name of the directory: ";
				cin >> dirName;
				queue<Tree<Directory>*> queue;
				queue.push(xmlfile.fileTree);
				while (!queue.empty())
				{
					DListIterator<Tree<Directory>*> iter = queue.front()->children->getIterator();
					while (iter.isValid())
					{
						queue.push(iter.item());
						iter.advance();
					}
					if (queue.front()->data.getName() == dirName) {
						cout << "Files in " << dirName << ":" << endl;
						cout << queue.front()->data.getFilesInfo("") << endl;
						cout << queue.front()->data.getFilesSize() << "b" << endl;
					}
					queue.pop();
				}
				cout << endl;
				break;
			}
			case 4: {
				TreeIterator<Directory> treeIter(xmlfile.fileTree);
				displayTree(treeIter, "");
				prune(treeIter);
				treeIter = TreeIterator<Directory>(xmlfile.fileTree);
				displayTree(treeIter, "");
				break;
			}
			case 5: {
				string fileName;
				cout << "Enter the name of the file: ";
				cin >> fileName;
				TreeIterator<Directory> iter(xmlfile.fileTree);
				string path = getPath(iter, "", fileName);
				cout << path << endl;
				break;
			}
			case 6: {
				string dirName;
				cout << "Enter the name of the directory: ";
				cin >> dirName;
				queue<Tree<Directory>*> queue;
				queue.push(xmlfile.fileTree);
				while (!queue.empty())
				{
					DListIterator<Tree<Directory>*> iter = queue.front()->children->getIterator();
					while (iter.isValid())
					{
						queue.push(iter.item());
						iter.advance();
					}
					if (queue.front()->data.getName() == dirName) {
						cout << "Files in " << dirName << ":" << endl;
						cout << queue.front()->data.getFilesInfo("") << endl;
						cout << "Total memory used: " << queue.front()->data.getFilesSize() << "b" << endl;
					}
					queue.pop();
				}
				cout << endl;
				break;
			}
			case 7: {
				appOn = false;
				break;
			}
			}
		}
		catch (exception e) {
			cout << "Error: " << e.what() << endl;
		}
	}
}
