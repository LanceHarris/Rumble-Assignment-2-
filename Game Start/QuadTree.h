#include <SFML/Graphics.hpp>
#include <list>
#include "Character.h"
#pragma once

class QuadTree
{
public:
	QuadTree(int level, sf::RectangleShape bounds);
	~QuadTree(void);
	void clear();
	void split();
	int getIndex(sf::Vector2f point);
	int insert(Enemy* enemy);
	std::vector<Enemy*> retrieve(std::vector<Enemy *> returntreeObjects, sf::Vector2f location);
	sf::RectangleShape bounds;
private:
	static const int MAXLEVELS = 15;
	static const int MAXDATA = 2;
	int level;
	std::list<struct Enemy*> data;
	QuadTree *nodes[4];
	Enemy test;
};