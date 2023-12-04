#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <class T>
class XMLLoader
{
	public:
	T* fileName;
	XMLLoader(T& fileName);
	bool load();
};

template <class T>
XMLLoader<T>::XMLLoader(T& fileName)
{
	this->fileName = &fileName;
}

template <class T>
bool XMLLoader<T>::load()
{
	return false;
}