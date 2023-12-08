#pragma once
#include "Tree.h"
#include "../FileManagementApp/Directory.h"
#include "../FileManagementApp/File.h"

template <class T>
class TreeIterator
{
public:
	Tree<T>* node;
	DListIterator<Tree<T>*> childIter;

	TreeIterator(Tree<T>* root);
	void resetIterator();
	void root();
	void up();
	void down();
	void childBack();
	void childForth();
	void childStart();
	void childEnd();
	void appendChild(T item);
	void prependChild(T item);
	void insertChildBefore(T item);
	void insertChildAfter(T item);
	void removeChild();
	bool childValid();
	T childItem();
	T item();
	void addToVector(File* file);
	string getFilesNames();
	string getNodeInfo();
};
template <class T>
TreeIterator<T>::TreeIterator(Tree<T>* root)
{
	node = root;
	resetIterator();
}

template <class T>
void TreeIterator<T>::resetIterator()
{
	if (node != nullptr)
	{
		childIter = node->children->getIterator();
	}
	else
	{
		childIter = nullptr;
	}
}

template <class T>
void TreeIterator<T>::root()
{
	if (node->parent != nullptr)
	{
		node = node->parent;
		root();
	}
	resetIterator();
}

template <class T>
void TreeIterator<T>::up()
{
	if (node->parent != nullptr)
	{
		node = node->parent;

	}
	resetIterator();
}

template <class T>
void TreeIterator<T>::down()
{
	if (childIter.isValid())
	{
		node = childIter.item();

	}
	resetIterator();
}

template <class T>
void TreeIterator<T>::childBack()
{
	if (childIter.isValid())
	{
		childIter.previous();
	}
}

template <class T>
void TreeIterator<T>::childForth()
{
	if (childIter.isValid())
	{
		childIter.advance();
	}
}

template <class T>
void TreeIterator<T>::childStart()
{
	if (childIter.isValid())
	{
		childIter.start();
	}
}

template <class T>
void TreeIterator<T>::childEnd()
{
	if (childIter.isValid())
	{
		childIter.end();
	}
}

template <class T>
void TreeIterator<T>::appendChild(T item)
{
	Tree<T>* temp = new Tree<T>(item);
	temp->parent = node;
	node->children->append(temp);
	resetIterator();
}

template <class T>
void TreeIterator<T>::prependChild(T item)
{
	Tree<T>* temp = new Tree<T>(item);
	temp->parent = node;
	node->children->prepend(temp);
	resetIterator();
}

template <class T>
void TreeIterator<T>::insertChildBefore(T item)
{
	Tree<T>* temp = new Tree<T>(item);
	temp->parent = node;
	node->children->insert(childIter, temp);

}

template <class T>
void TreeIterator<T>::insertChildAfter(T item)
{

	Tree<T>* temp = new Tree<T>(item);
	temp->parent = node;
	childIter.advance();
	node->children->insert(childIter, temp);
	childIter.previous();
	childIter.previous();

}

template <class T>
void TreeIterator<T>::removeChild()
{
	childIter = node->children->remove(childIter);

}

template <class T>
bool TreeIterator<T>::childValid()
{
	return childIter.isValid();
}

template <class T>
T TreeIterator<T>::childItem()
{
	return childIter.item()->data;
}

template <class T>
T TreeIterator<T>::item()
{
	return node->data;
}

template <class T>
void TreeIterator<T>::addToVector(File* file)
{
	childIter.item()->data.files.push_back(file);
}

template <class T>
string TreeIterator<T>::getFilesNames()
{
	string names = "";
	if (childIter.item() != nullptr) {
		for (int i = 0; i < childIter.item()->data.files.size(); i++)
		{
				names += childIter.item()->data.files[i]->getName() + "\n";
		}
	}
	return names;
}

template <class T>
string TreeIterator<T>::getNodeInfo()
{
	string info = "";
	info += "Name: " + childIter.item()->data.getName() + "\n";
	info += "Files: \n";
	info += getFilesNames();
	return info;
}