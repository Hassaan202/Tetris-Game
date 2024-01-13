#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Well.h"
using namespace std;
using namespace sf;
#include <fstream>

#define Rows 4
#define Columns 4
#define CellSize 28

//abstract class
class Tetrimino {
	friend class Game;
protected:
	int color;
	Vector2f refLocation;
	int currentRotationAngle;
	Sprite mino;
	Texture texture;
	int arr[Rows * Columns] = { 0 };

public:
	Tetrimino();
	void draw(RenderWindow& window); //draws the whole tetrimino
	void draw(RenderWindow& window, int, int); //draws a single square in the map
	int rotate(int, int, int);
	int rotate(int, int);
	int getColor();
	bool doesTetriminoFit(int, int, int, Well);
	void initializeValues();
 };

class I :public Tetrimino {
	
public:
	I();
};

class J :public Tetrimino {

public:
	J();
};

class L :public Tetrimino {

public:
	L();
};

class O :public Tetrimino {

public:
	O();
};

class S :public Tetrimino {

public:
	S();
};

class T :public Tetrimino {

public:
	T();
};

class Z :public Tetrimino {

public:
	Z();
};

