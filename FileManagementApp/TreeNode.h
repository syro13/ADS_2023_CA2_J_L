#pragma once
#include <iostream>
#include <string>

using namespace std;

class TreeNode {
protected:
	string name;
public:
	virtual ~TreeNode() = default;
	virtual string getName() = 0;
	virtual void setName(string name) = 0;
	virtual void print() = 0;
};