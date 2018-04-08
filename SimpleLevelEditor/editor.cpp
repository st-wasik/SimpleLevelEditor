#include "editor.h"
#include "cmath"
#include "string"
using namespace std;

template <typename T>
ostream& operator<<(ostream& cout, sf::Vector2<T> vect)
{
	cout << vect.x << " " << vect.y;
	return cout;
}

sf::Vector2f& operator/(sf::Vector2f& vect, int div)
{
	if (div != 0)
		return sf::Vector2f(vect.x / div, vect.y / div);
	return vect;
}

sf::Vector2f& operator*(sf::Vector2f& vect, int mult)
{
	return sf::Vector2f(vect.x * mult, vect.y * mult);
}

float distanceOf(sf::Vector2f A, sf::Vector2f B)
{
	return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}




editor::editor() : zoom(1), currentTileType(0), windowTitle("SimpleLevelEditor (v0.1) for [BlockyBlocks] Project"),
	windowResolution(1000,800)
{
	window.setVerticalSyncEnabled(true);

	currentView.setSize(windowResolution);
	currentView.setCenter(50, 50);
	currentView.zoom(1.5);

	window.setView(currentView);
}

editor::~editor()
{
}

void editor::run()
{
	cout << "S.L.E. v0.1   (C) BB 15.10.2016" << endl;
	cout << "MENU --------------------------\n" << endl;
	cout << "1- Create new level" << endl;
	cout << "2- Load existing level" << endl;
	cout << "0- Exit" << endl;
	bool loopRun = 1;
	do{
		unsigned int choose = 0;
		cout << " > ";
		cin >> choose;
		string filename;

		switch (choose)
		{
		case 1: levelPointer = new level(); loopRun = 0;  break;
		case 2:
			cout << "Type filename to load level" << endl;
			cout << " FILENAME: ";
			cin >> filename;
			levelPointer = new level(filename); loopRun = 0; break;
		case 0: return;
		default: cout << "Wrong number. Type a correct number! " << endl;
		}

		
	} while (loopRun);
	
	window.create(sf::VideoMode(windowResolution.x, windowResolution.y, 32), windowTitle, sf::Style::Close);

	while (window.isOpen())
	{

		mouseOld = mouse;
		mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window), currentView);

		window.setView(currentView);

		// EVENT LOOP BEGINNING
		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				window.close();

			if (event.type == sf::Event::MouseWheelMoved)
			{
				if (event.mouseWheel.delta == 1 && zoom > -1)
				{
					currentView.zoom(.5);
					zoom--;
				}
				if (event.mouseWheel.delta == -1 && zoom < 4)
				{
					currentView.zoom(2);
					zoom++;
				}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::F2)
				{
					string filename;
					cout << "Type filename to save level" << endl;
					cout << " FILENAME: ";
					cin >> filename;

					levelPointer->saveToFile((filename + ".lvl").c_str());
				}
			}
		} 
		// EVENT LOOP END

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (
				(currentView.getCenter() + (mouse - mouseOld)).x < levelPointer->levelSize.x * 64 &&
				(currentView.getCenter() + (mouse - mouseOld)).y < levelPointer->levelSize.y * 64 &&
				(currentView.getCenter() + (mouse - mouseOld)).x > 0 &&
				(currentView.getCenter() + (mouse - mouseOld)).y > 0
				)
				currentView.move((mouse - mouseOld) / 2);
		}

		delta_time = deltaClock.getElapsedTime().asMilliseconds();
		deltaClock.restart();

		window.clear(sf::Color::Black);

		levelPointer->update(mouse, mouseOld);
		levelPointer->draw(window);

		window.display();
	}
}
