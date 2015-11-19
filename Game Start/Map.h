/*
*	Map.h
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 24 October 2015
*
*/

#pragma once

class Character;

#include <SFML/Graphics.hpp>
#include <iostream>


using namespace std;

class Map

{
public:
	static const int ROW_COUNT = 35;
	static const int COLUMN_COUNT = 45;

	enum Tile {
		TileOut = -1,
		TileEmpty = 0,
		TileWall = 1,
		tileWallFront = 2,
		tileWallFrontTorch = 3,
		transition = 4,
		statStore = 5,
		itemStore = 6,
		itemFrontWall = 7,
		statWallFront = 8,
		barrel = 9,
		pillarTop = 10,
		pillarBottom = 11,
		door = 12,
		oldMan = 13,
	};

	int curMap; //keeps track of current map
	Tile getTile(int row, int column);
	bool isCollision(int row, int column);
	sf::Sprite getSprite();
	Map(int winX, int winY, int newMap[Map::ROW_COUNT][Map::COLUMN_COUNT]);
	~Map(void);
	void setMap(int newMap[Map::ROW_COUNT][Map::COLUMN_COUNT], int mapValue);
	bool isTile(int row, int column, Map::Tile tile);
	int getCurrentMap();
	void drawMap(sf::RenderWindow &window, sf::Sprite &dungeonStage, sf::Sprite &shopStage);

	void drawMap();

	int default_map[Map::ROW_COUNT][Map::COLUMN_COUNT];

private:
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Texture wallTexture;
	sf::Sprite wallSprite;
};

