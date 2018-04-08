#pragma once
#include "tile.h"
class level
{
public:
	level();
	level(string filename);
	~level();

	sf::Vector2i levelSize;
	tile ***levelPointer;

	void draw(sf::RenderWindow&);
	void update(sf::Vector2f&, sf::Vector2f&);
	int currentTileType;

	void saveToFile(string filename);

};

