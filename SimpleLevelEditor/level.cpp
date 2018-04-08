#include "level.h"
#include "sstream"
#include "cstdint"
#include "iomanip"
#include "fstream"

float round3(float value)
{
	return static_cast<int>(value * 1000) / static_cast<float>(1000);
}

string convert(unsigned long float bin)
{
	ostringstream result;
	result.clear();
	int pow = 0;

	while (bin > 1024)
	{
		bin = bin / 1024;
		pow++;
	}
	bin++;

	result << round3(bin);
	if (pow == 1)
		result << " k";
	else if (pow == 2)
		result << " M";
	else if (pow == 3)
		result << " G";
	result << "B";
	return result.str();

}



level::level() : currentTileType(0)
{
	char x;
	do
	{
		cout << "Type level size \nX > ";
		cin >> levelSize.x;
		cout << "Y > ";
		cin >> levelSize.y;

		cout << "This size of level needs " << convert(sizeof(tile)*levelSize.x*levelSize.y) << " of RAM. " << flush;
		do{
			x = 0;
			cout << "\n Continue ? [y / n] : " << flush;
			cin >> x;
		} while (x != 'y' && x != 'Y' && x != 'n' && x != 'N');
		cout << endl;
	} while (x == 'n' || x == 'N');

	cout << "Generating level array... " << flush;
	try{
		levelPointer = new tile**[levelSize.y];

		for (int i = 0; i < levelSize.y; i++)
			levelPointer[i] = new tile*[levelSize.x];

		for (int i = 0; i < levelSize.y; i++)
			for (int j = 0; j < levelSize.x; j++)
				levelPointer[i][j] = new tile;

		for (int i = 0; i < levelSize.y; i++)
			for (int j = 0; j < levelSize.x; j++)
			{
				levelPointer[i][j]->tileType = 0;
				levelPointer[i][j]->setTile(j, i);
			}
	}
	catch (bad_alloc)
	{
		cerr << "Not enough RAM!" << endl;
		return;
	}
	cout << "Done!" << endl;

}

level::level(string filename) : currentTileType(0)
{
	ifstream fin;
	fin.open(filename.c_str());
	if (fin)
	{
		fin >> levelSize.x >> levelSize.y;
		try{
			levelPointer = new tile**[levelSize.y];

			for (int i = 0; i < levelSize.y; i++)
				levelPointer[i] = new tile*[levelSize.x];

			for (int i = 0; i < levelSize.y; i++)
				for (int j = 0; j < levelSize.x; j++)
					levelPointer[i][j] = new tile;

			for (int i = 0; i < levelSize.y; i++)
				for (int j = 0; j < levelSize.x; j++)
					levelPointer[i][j]->setTile(j, i);
		}
		catch (bad_alloc)
		{
			cerr << "Not enough RAM!" << endl;
			return;
		}

		for (int i = 0; i < levelSize.y; i++)
			for (int j = 0; j < levelSize.x; j++)
			{
				int x;
				fin >> x;
				levelPointer[i][j]->tileType = x;
				levelPointer[i][j]->setTile(j, i);
				levelPointer[i][j]->update();
			}
	}
	else
	{
		cerr << "Cannot open file to load level!" << endl;
		return;
	}
	cout << "Done!" << endl;

}

level::~level()
{
	for (int i = 0; i < levelSize.y; i++)
		for (int j = 0; j < levelSize.x; j++)
			delete levelPointer[i][j];

	for (int i = 0; i < levelSize.y; i++)
		delete levelPointer[i];

	delete levelPointer;
}

void level::draw(sf::RenderWindow &window)
{
	sf::Vector2f center = window.getView().getCenter(), size = window.getView().getSize();
	int Ax = (center.x - (size.x / 2)) / 64 - 1, Ay = (center.y - (size.y / 2)) / 64 - 1,
		Bx = (center.x + (size.x / 2)) / 64 + 1, By = (center.y + (size.y / 2)) / 64 + 1;

	if (Ax < 0) Ax = 0;
	if (Ay < 0) Ay = 0;
	if (Bx > levelSize.x) Bx = levelSize.x;
	if (By > levelSize.y) By = levelSize.y;

	//cout << "\r" << Ax << ":" << Ay << " " << Bx << ":" << By << "   " << flush;

	for (int i = Ay; i < By; i++)
		for (int j = Ax; j < Bx; j++)
			levelPointer[i][j]->draw(window);
}

void level::update(sf::Vector2f &mouse, sf::Vector2f& mouseOld)
{
	int X = mouse.x / tile::tileSize.x;
	int Y = mouse.y / tile::tileSize.y;
	int Xold = mouseOld.x / tile::tileSize.x;
	int Yold = mouseOld.y / tile::tileSize.y;

	if ((Xold >= 0 && Xold < levelSize.x) && (Yold >= 0 && Yold < levelSize.y))
	{
		levelPointer[Yold][Xold]->setNormal();
	}

	if ((X >= 0 && X < levelSize.x) && (Y >= 0 && Y < levelSize.y))
	{
		levelPointer[Y][X]->setBold();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		currentTileType = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		currentTileType = 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		currentTileType = 3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		currentTileType = 4;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		currentTileType = 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		currentTileType = 0;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (X >= 0 && X < levelSize.x && Y >= 0 && Y < levelSize.y)
		{
			levelPointer[Y][X]->tileType = currentTileType;
			levelPointer[Y][X]->update();
		}
	}

	if (
		sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)
		)
	{
		for (int i = 0; i < levelSize.y; i++)
			for (int j = 0; j < levelSize.x; j++)
			{
				levelPointer[i][j]->tileType = 0;
				levelPointer[i][j]->update();
			}
	}

}

void level::saveToFile(string filename)
{
	ofstream fout;
	fout.open(filename.c_str(), ios::out & ios::trunc);
	if (fout)
	{
		fout << levelSize.x << ' ' << levelSize.y << '\n';

		for (int i = 0; i < levelSize.y; i++)
		{
			for (int j = 0; j < levelSize.x; j++)
			{
				fout << levelPointer[i][j]->tileType << ' ';
			}
			fout << '\n';
		}
		fout << flush;
		fout.close();
		cout << "Level saved. " << endl;
	}
	else
	{
		cerr << "Cannot create file to save level!" << endl;
	}
}