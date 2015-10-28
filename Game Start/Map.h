/*
*	Map.h
*	Rumble
*
*	Created by: Reuben Dales, Lance Donnell, Lance Harris, Josh Prow.
*	Dated: 24 October 2015
*
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Map

{
public:
	static const int ROW_COUNT = 35;
	static const int COLUMN_COUNT = 45;

	enum Tile {
		TileOut = -1,
		TileEmpty = 0,
		TileWall = 1,
		TileTrap = 2,
	};

	Tile getTile(int row, int column);
	bool isCollision(int row, int column);
	sf::Sprite getSprite();
	Map(int, int);
	~Map(void);

private:
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Texture wallTexture;
	sf::Sprite wallSprite;

	static const int Map::DEFAULT_MAP[Map::ROW_COUNT][COLUMN_COUNT];
};

