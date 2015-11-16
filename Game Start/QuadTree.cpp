#include "QuadTree.h"

QuadTree::QuadTree(int level, sf::RectangleShape bounds)
{
	this->level = level;
	this->bounds = bounds;
	this->nodes[0] = nullptr;
	this->nodes[1] = nullptr;
	this->nodes[2] = nullptr;
	this->nodes[3] = nullptr;
}

void QuadTree::clear(){
	for (int i = 0; i < 4; i ++){
		if (nodes[i] != NULL){
			nodes[i]->clear();
			nodes[i] = NULL;
		}
	}
	data.clear();
}

void QuadTree::split(){
	float subWidth = bounds.getSize().x / 2;
	float subHeight = bounds.getSize().y / 2;
	float x = bounds.getPosition().x;
	float y = bounds.getPosition().y;

	sf::RectangleShape rectangle(sf::Vector2f(subWidth,subHeight));

	//NW
	rectangle.setPosition(x,y);
	nodes[0] = new QuadTree(level+1,rectangle);

	//NE
	rectangle.setPosition(x + subWidth, y);
	nodes[1] = new QuadTree(level+1,rectangle);

	
	//SW
	rectangle.setPosition(x, y + subHeight);
	nodes[2] = new QuadTree(level+1,rectangle);
	
	//SE
	rectangle.setPosition(x + subWidth, y + subHeight);
	nodes[3] = new QuadTree(level+1,rectangle);
}

int QuadTree::getIndex(sf::Vector2f point){
	sf::Vector2f midPoint = bounds.getPosition() + sf::Vector2f(bounds.getSize().x / 2,bounds.getSize().y / 2);
	
	//find location of point
	bool north = (point.y < midPoint.y && point.y > bounds.getPosition().y);
	bool south = (point.y >= midPoint.y && point.y <= bounds.getPosition().y + bounds.getSize().y);
	if (point.x <= midPoint.x && point.x > bounds.getPosition().x){ //West
		if (north){
			return 0;
		}else if (south){
			return 2;
		}
	}else if (point.x > midPoint.x && point.x <= bounds.getPosition().x + bounds.getSize().x){ //East
		if (north){
			return 1;
		}else if(south){
			return 3;
		}
	}
	return -1;
}

int QuadTree::insert(Enemy* enemy){
	if (nodes[0] != nullptr){
		int index = getIndex((sf::Vector2f(enemy->getRow()*24,enemy->getColumn()*24)));
		nodes[index]->insert(enemy);
		return 1; // inserted :)
	}

	data.push_front(enemy);

	if (level < MAXLEVELS && data.size() > MAXDATA){
		if (nodes[0] == nullptr){
			split();
		}
		int i = data.size();
		while (i > 0 ){
			Enemy *lastItem = data.back();
			int index = getIndex((sf::Vector2f(lastItem->getRow()*24,lastItem->getColumn()*24)));
			if (index != -1){
				nodes[index]->insert(lastItem);
			}
			data.pop_back();
			i-=1;
		}
	}
}

std::vector<Enemy*> QuadTree::retrieve(std::vector<Enemy *> returntreeObjects, sf::Vector2f location){
	int index = getIndex(location);
	if (index != -1 && nodes[0] != NULL){
		nodes[index]->retrieve(returntreeObjects, location);
	}
	returntreeObjects.insert(returntreeObjects.end(), data.begin(), data.end());

	return returntreeObjects;
}

QuadTree::~QuadTree(void)
{
	for (int i = 0; i < 4; i ++){
		if (nodes[i] != NULL){
			nodes[i]->clear();
			nodes[i] = NULL;
		}
	}
	data.clear();
}
