#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"
#include "level.h"

class editor final
{
public:
	editor();
	~editor();
	double delta_time;
	void run();

private:
	level* levelPointer;
	sf::View currentView;
	sf::Vector2f windowResolution;
	sf::Event event;
	sf::Vector2f mouse;
	sf::Vector2f mouseOld;
	sf::RenderWindow window;
	sf::Clock deltaClock;
	string windowTitle;
	int currentTileType;
	int zoom;
};

