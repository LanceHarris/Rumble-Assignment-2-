#pragma once
#include <string.h>
#include <iostream>

using namespace std;

class Item
{
public:
	int price;
	string description;

	Item(void);
	~Item(void);

	int getPrice();
	string getDescription();
};

