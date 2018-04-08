#include "tile.h"

sf::Color invertColor(const sf::Color& color)
{
	return sf::Color(255 - color.r, 255 - color.g, 255 - color.b);
}

const sf::Vector2f tile::tileSize(64, 64);

sf::Texture tile::texture[10];

tile::tile() 
{
	tileShape.setSize(sf::Vector2f(64, 64));
	tileShape.setFillColor(sf::Color(32, 32, 32));
	tileShape.setOutlineThickness(-3);
	tileShape.setOutlineColor(sf::Color(127, 127, 127));
}

tile::~tile()
{
}

void tile::draw(sf::RenderWindow &window)
{
	window.draw(tileShape);
}

void tile::setTile(int x, int y)
{
	tileShape.setPosition(x*tileSize.x, y*tileSize.y);
}

void tile::update()
{
	if (tileType == 0)
		tileShape.setFillColor(sf::Color(32, 32, 32));
	if (tileType == 1)
		tileShape.setFillColor(sf::Color(255, 0, 127));
	if (tileType == 2)
		tileShape.setFillColor(sf::Color(64, 192, 192));
	if (tileType == 3)
		tileShape.setFillColor(sf::Color(192, 192, 8));
	if (tileType == 4)
		tileShape.setFillColor(sf::Color(8, 8, 8));
	if (tileType == 5)
		tileShape.setFillColor(sf::Color(32, 127, 64));
}

void tile::loadTextures()
{

	/*texture[1].loadFromFile("textures/0HD.png");
	texture[1].loadFromFile("textures/1.png");
	texture[2].loadFromFile("textures/2.png");
	texture[3].loadFromFile("textures/3.png");
	texture[4].loadFromFile("textures/4HD.png");*/
}

void tile::setBold()
{
	tileShape.setOutlineColor(invertColor(tileShape.getFillColor()));
	tileShape.setOutlineThickness(-5);
}

void tile::setNormal()
{
	tileShape.setOutlineColor(sf::Color(127, 127, 127));
	tileShape.setOutlineThickness(-3);
}