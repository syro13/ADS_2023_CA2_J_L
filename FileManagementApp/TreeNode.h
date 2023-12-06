#pragma once
#include <iostream>
#include <string>

using namespace std;

class TreeNode {
public:
	virtual string getName() = 0;
	virtual void setName(string name) = 0;

};