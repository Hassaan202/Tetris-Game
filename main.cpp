#include <SFML/Audio.hpp>
#include <iostream>
#include "menu.h"
#include "game.h"


int main() {

	RenderWindow window(VideoMode(896, 672), "TETRIS GAME", Style::Titlebar|Style::Close);
	window.setFramerateLimit(60);

	RenderWindow MenuWindow(VideoMode(700, 650), "TETRIS GAME");
	Menu menu(MenuWindow.getSize().x, MenuWindow.getSize().y);
	MenuWindow.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	//MENU WINDOW
	bool runGame = false;
	bool closeWindow = false;
	while (MenuWindow.isOpen()) {
		Event event;
		while (MenuWindow.pollEvent(event)) {
			//events
			switch (event.type) {
			case Event::Closed:
				MenuWindow.close();
				break;
			case Event::KeyPressed:

				switch (event.key.code) {
				case Keyboard::Up:
					menu.MoveUp();
					break;
				case Keyboard::Down:
					menu.MoveDown();
					break;
				case Keyboard::Return:
					switch (menu.getSelectedItemIndex()) {
					case 0:
						runGame = true;
						MenuWindow.close();
						break;
					case 1: //opening the high score window
						menu.setIsHighScoreOpen(true);
						menu.retrieveHighScore();
						break;
					case 2:
						MenuWindow.close();
						cout << "Exit!!!\n";
						break;
					}
					break;
				}
				break;
			}
		}

		if (menu.getIsHighScoreOpen() && Keyboard::isKeyPressed(Keyboard::Escape)) {
			menu.setIsHighScoreOpen(false);
		}
		if (closeWindow) {
			MenuWindow.close();
		}

		MenuWindow.clear();
		menu.draw(MenuWindow);
		MenuWindow.display();
	}

	Game game;
	if (runGame==true) {
		cout << "ENTER YOUR NAME: ";
		game.getNameInput();		
	}		

	Clock clock;
	Music gameMusic;
	if (!gameMusic.openFromFile("GameMusic.wav")) {
		return EXIT_FAILURE;
	}
	gameMusic.setVolume(10);
	gameMusic.setLoop(true);
	gameMusic.setLoopPoints(sf::Music::TimeSpan(sf::seconds(5), sf::seconds(110)));

	//GAME RUN WINDOW
	bool isGameOver = false;
	if (runGame == true) {
		gameMusic.play();
		while (window.isOpen()) {
			Event event;
			while (window.pollEvent(event)) {
				//events
				switch (event.type) {
				case Event::Closed:
					window.close();
					break;
				case Event::Resized:
					cout << event.size.width << " : " << event.size.height << endl;
					break;			
				}
			}
			if (isGameOver == true) {
				window.close();
				game.updateHighScore();
				cout << "Game over!\n";
				gameMusic.stop();
			}

			window.clear();	

			Time time = clock.getElapsedTime();
	
			isGameOver = game.update(time);
			game.draw(window);		 
			clock.restart().asSeconds();
			window.display();
		}
	}
}
