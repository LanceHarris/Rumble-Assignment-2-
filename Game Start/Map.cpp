/*
*	Map.cpp
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 24 October 2015
*
*/


#include "Map.h"


Map::Map(int winX, int winY, int newMap[Map::ROW_COUNT][Map::COLUMN_COUNT])
{
	curMap = 0;

	if (!texture.loadFromFile("tile2.jpg"))
	{
		std::cout << "Error loading resource map.bmp" << std::endl;
	}
	texture.setRepeated(true);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0,0,winX,winY));

	for(int i = 0; i < Map::ROW_COUNT;i++)
	{
		for(int j = 0; j < Map::COLUMN_COUNT;j++)
		{
			default_map[i][j] = newMap[i][j];
		}
	}
}

Map::Tile Map::getTile(int row, int column)
{
	return Tile(default_map[row][column]);
}

bool Map::isCollision(int row, int column)
{
	Map::Tile tile = getTile(row, column);
	if (tile != Map::Tile::TileEmpty && tile != Map::Tile::transition && tile != Map::Tile::pillarBottom && tile != Map::Tile::door)
	{
		return true;
	}

	return false;
}

bool Map::isTile(int row, int column, Map::Tile aTile)
{
	Map::Tile tile = getTile(row, column);
	if (tile == aTile)
	{
		return true;
	}

	return false;
}

sf::Sprite Map::getSprite()
{
	return sprite;
}

void Map::setMap(int newMap[Map::ROW_COUNT][Map::COLUMN_COUNT], int mapValue)
{
	for(int i = 0; i < Map::ROW_COUNT;i++)
	{
		for(int j = 0; j < Map::COLUMN_COUNT;j++)
		{
			default_map[i][j] = newMap[i][j];
		}
	}
	curMap = mapValue;
}

int Map::getCurrentMap()
{
	return curMap;
}

void Map::drawMap(sf::RenderWindow &window, sf::Sprite &dungeonStage, sf::Sprite &shopStage)
{
	if(curMap == 0)
	{
		window.draw(dungeonStage);
	}
	else
	{
		window.draw(shopStage);
	}
}

Map::~Map(void)
{
}
