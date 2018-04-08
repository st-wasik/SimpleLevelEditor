#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"
using namespace std;

class tile
{
public:
	tile();
	~tile();

	static void loadTextures();
	static sf::Texture texture[10];
	static const sf::Vector2f tileSize;
	unsigned int tileType;

	void draw(sf::RenderWindow &window);
	void setTile(int x, int y);
	void update();

	void setBold();
	void setNormal();

private:
	sf::RectangleShape tileShape;
};

