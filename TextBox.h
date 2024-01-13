#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace sf;

#define DELETE 8
#define ENTER 10

class TextBox {
private:
	Texture texture;
	Font font;
	Text textBox;
	string str;
	int limit;
	bool dataSubmit;

	bool getInput(int charTyped) {
		if (charTyped == DELETE) {
			deleteLastChar();
			return false;
		}
		else if (charTyped == ENTER) {
			dataSubmit = true;
			return true;
		}
		else {
			while (str.length() < limit) {
				str += charTyped;
			 }
			textBox.setString(str);
			return false;
		}
	
	}

	void deleteLastChar(){
		if (str.length() == 0) {
			return;
		}
		else {
			string temp;
			temp = str.substr(0, str.length() - 1);
			str = "";
			str = temp;
		}
	}

public:
	TextBox(){
		if (!font.loadFromFile("game_over.ttf")) {
			return;
		}
		textBox.setPosition(Vector2f(200, 200));
		textBox.setFont(font);
		textBox.setFillColor(Color::Black);
		textBox.setOutlineColor(Color::White);
		textBox.setOutlineThickness(2);
		textBox.setCharacterSize(100);
		str = "";
		limit = 20;
		dataSubmit = false;
	}

	void draw(RenderWindow& window) {
		window.draw(textBox);
	}

	bool inputText(Event event) {
		int charType = event.text.unicode;
		return (getInput(charType));
	}


};
