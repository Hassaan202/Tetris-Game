#include "Menu.h"

Menu::Menu(float width, float height)
{
	
	//general menu
	if (!font.loadFromFile("game_over.ttf")) {
		return;
	}
	if (!texture.loadFromFile("Tetris_Logo.jpg")) {
		return;
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 50, 1400, 1400));
	sprite.setScale(Vector2f(0.5, 0.65));

	if (!hTex.loadFromFile("Tetris.jpg")) {
		return;
	}
	hSprite.setTexture(hTex);
	hSprite.setTextureRect(IntRect(0, 0, 3000, 3000));
	hSprite.setScale(Vector2f(0.3, 0.3));

	menu[0].setFont(font);
	menu[0].setFillColor(Color::Red);
	menu[0].setString("START");
	menu[0].setCharacterSize(60);
	menu[0].setScale(Vector2f(1.1, 1.1));
	menu[0].setPosition(Vector2f(width / 2 - 75, height / 4 * 2));
	menu[0].setOutlineColor(Color::Yellow);
	menu[0].setOutlineThickness(2);

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("HIGH SCORES");
	menu[1].setCharacterSize(60);
	menu[1].setPosition(Vector2f(width / 2 - 75, height / 4 * 2.5));
	menu[1].setOutlineColor(Color::Black);
	menu[1].setOutlineThickness(2);

	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("EXIT");
	menu[2].setCharacterSize(60);
	menu[2].setPosition(Vector2f(width / 2 - 75, height / 4 * 3));
	menu[2].setOutlineColor(Color::Black);
	menu[2].setOutlineThickness(2);

	selectedItemIndex = 0;

	//high score
	isHighScoreOpen = false;
	for (int i = 0; i < 6; i++) {
		highScoreText[i].setFont(font);
		highScoreText[i].setFillColor(Color::Black);
		highScoreText[i].setCharacterSize(100);
		highScoreText[i].setOutlineThickness(2);
		highScoreText[i].setOutlineColor(Color::White);
	}
	highScoreText[0].setString("HIGH SCORES");

	returnMessage.setFont(font);
	returnMessage.setFillColor(Color::Black);
	returnMessage.setCharacterSize(70);
	returnMessage.setPosition(Vector2f(0, -30));
	returnMessage.setString("Press ESC to return");
	returnMessage.setOutlineThickness(2);
	returnMessage.setOutlineColor(Color::White);
}

void Menu::draw(RenderWindow& window)
{
	if (!isHighScoreOpen) {
		window.draw(sprite);
		for (int i = 0; i < 3; i++) {
			window.draw(menu[i]);
		}
	}
	else {
		window.draw(hSprite);
		window.draw(returnMessage);
		for (int i = 0; i < 6; i++) {
			highScoreText[i].setPosition(Vector2f(230, 50 + (i * 80)));
			window.draw(highScoreText[i]);
		}
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setFillColor(Color::White);
		menu[selectedItemIndex].setScale(Vector2f(0.90909, 0.90909));
		menu[selectedItemIndex].setOutlineColor(Color::Black);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(Color::Red);
		menu[selectedItemIndex].setScale(Vector2f(1.1, 1.1));
		menu[selectedItemIndex].setOutlineColor(Color::Yellow);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < 3) {
		menu[selectedItemIndex].setFillColor(Color::White);
		menu[selectedItemIndex].setScale(Vector2f(0.90909, 0.90909));
		menu[selectedItemIndex].setOutlineColor(Color::Black);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(Color::Red);
		menu[selectedItemIndex].setScale(Vector2f(1.1, 1.1));
		menu[selectedItemIndex].setOutlineColor(Color::Yellow);
	}
}

void Menu::retrieveHighScore()
{
	string temp;
	read.open("highScoreData.txt");
	//data copied to the array
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 2; j++) {
			getline(read, temp);
			arr[i][j] = temp;
		}
	}
	read.close();
	for (int i = 1; i < 6; i++) {
		highScoreText[i].setString(arr[i -1][0] + " : " + arr[i - 1][1]);
	}
}


