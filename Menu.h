#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include <fstream>
using namespace std;
using namespace sf;

class Menu
{
private:
	string arr[5][2];
	ifstream read;
	bool isHighScoreOpen;
	Texture hTex;
	Sprite hSprite;
	Text highScoreText[6];
	Text returnMessage;

	Texture texture;
	Sprite sprite;
	int selectedItemIndex;
	Font font;
	Text menu[3];

public:
	Menu(float width, float height);
	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	inline int getSelectedItemIndex() { return selectedItemIndex; }
	void setIsHighScoreOpen(bool flag) { isHighScoreOpen = flag; }
	bool getIsHighScoreOpen() { return isHighScoreOpen; }
	void retrieveHighScore();

};

