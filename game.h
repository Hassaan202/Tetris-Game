#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Tetrimino.h"
#include <fstream>
#include <sstream>

class Game {
	Well matrix;
	Tetrimino* TetrisBlocksArr[7];

	Texture tex1;
	Texture tex2;
	Texture tex3;
	Texture tex4;

	Sprite Background;
	Sprite Walls;
	Sprite clearLine;
	Sprite gameBack;

	Font font;
	Text scoreText;
	Text levelText;
	Text gameTitle;
	Text lineText;
	
	SoundBuffer soundBuff;
	Sound lineClear;

	string scoreStr;
	string levelStr;
	string lineStr;
	int currXPos = 0;
	int currMino = 0;
	int speedCounter = 0;
	int currentSpeed = 0;
	int noOfLinesCleared = 0;
	int linesCount = 0;
	int difficultyLevel = 0;
	int currentLevel = 0;
	int score = 0;
	int counter = 0;

	bool isRotatedHold = 0;
	bool gameOver = 0;
	bool isRightPressed = false;
	bool isLeftPressed = false;

	//high score functionality
	string highScoreArr[5][2];
	ofstream highScoresWrite;
	ifstream highScoreRead;

	//current player name
	bool isTextBoxOpen;
	string str;  
	int limit;
	Text currentName;

public:
	Game() {
		TetrisBlocksArr[0] = new I;
		TetrisBlocksArr[1] = new J;
		TetrisBlocksArr[2] = new L;
		TetrisBlocksArr[3] = new S;
		TetrisBlocksArr[4] = new O;
		TetrisBlocksArr[5] = new T;
		TetrisBlocksArr[6] = new Z;
		if (!tex1.loadFromFile("BTile.jpg")) {
			return;
		}
		Background.setTexture(tex1);
		if (!tex2.loadFromFile("wall.jpg")) {
			return;
		}
		Walls.setTexture(tex2);
		if (!tex3.loadFromFile("clearTile.jpg")) {
			return;
		}
		clearLine.setTexture(tex3);
		if (!tex4.loadFromFile("gameBack.jpg")) {
			return;
		}
		gameBack.setTexture(tex4);

		while (!font.loadFromFile("game_over.ttf")) {
			return;
		}
		scoreText.setFont(font);
		levelText.setFont(font);
		lineText.setFont(font);

		gameTitle.setFont(font);
		gameTitle.setString("TETRIS");
		gameTitle.setFillColor(Color::Cyan);
		gameTitle.setPosition(Vector2f(400, -60));
		gameTitle.setCharacterSize(150);
		gameTitle.setOutlineColor(Color::Black);
		gameTitle.setOutlineThickness(2);

		scoreText.setFillColor(Color::Cyan);
		scoreText.setPosition(Vector2f(400, 150));
		scoreText.setCharacterSize(150);
		scoreText.setOutlineColor(Color::Black);
		scoreText.setOutlineThickness(2);

		levelText.setFillColor(Color::Cyan);
		levelText.setPosition(Vector2f(400, 260));
		levelText.setCharacterSize(150);
		levelText.setOutlineColor(Color::Black);
		levelText.setOutlineThickness(2);

		lineText.setFillColor(Color::Cyan);
		lineText.setPosition(Vector2f(400, 370));
		lineText.setCharacterSize(150);
		lineText.setOutlineColor(Color::Black);
		lineText.setOutlineThickness(2);

		if (!soundBuff.loadFromFile("ClearSound.wav")) {
			return;
		}
		lineClear.setBuffer(soundBuff);
		lineClear.setVolume(40);

		currXPos = xComp / 2 - 1;
		currMino = rand() % 7;
		speedCounter = 0;
		currentSpeed = 60;
		noOfLinesCleared = 0;
		linesCount = 0;
		difficultyLevel = 4;
		currentLevel = 1;
		score = 0;

		isRotatedHold = false;
		gameOver = false;
		isRightPressed = false;
		isLeftPressed = false;

		//high score functionality
		string temp;
		highScoreRead.open("highScoreData.txt");
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 2; j++) {
				getline(highScoreRead, temp);
				highScoreArr[i][j] = temp;
			}
		}
		//current name
		isTextBoxOpen = false;
		limit = 20;
		if (!font.loadFromFile("game_over.ttf")) {
			return;
		}
		currentName.setPosition(Vector2f(400, 40));
		currentName.setFont(font);
		currentName.setFillColor(Color::Cyan);
		currentName.setOutlineColor(Color::Black);
		currentName.setOutlineThickness(2);
		currentName.setCharacterSize(150);
	}


	~Game() {
		for (int i = 0; i < 7; i++) {
			delete TetrisBlocksArr[i];
		}
	}


	void draw(RenderWindow &window) {
		//drawing the map
		window.draw(gameBack);
		for (int i = 0; i < yComp; i++) {
			for (int j = 0; j < xComp; j++) {
				if (matrix.getArr(i * xComp + j) == 0) {
					Background.setPosition(Vector2f(j * CellSize, i * CellSize));
					window.draw(Background); //background
				}
				else if (matrix.getArr(i * xComp + j) == 9) {
					Walls.setPosition(Vector2f(j * CellSize, i * CellSize));
					window.draw(Walls);
				}
				else if (matrix.getArr(i * xComp + j) == 8) {
					clearLine.setPosition(Vector2f(j * CellSize, i * CellSize));
					window.draw(clearLine);
					for (int i = 0; i < 100000; i++) {
						//sleep
					}
					lineClear.play();
					//shift the array indexes
					for (int yVal = i; yVal > 0; yVal--) {
						for (int xVal = 1; xVal < xComp - 1; xVal++) {
							matrix.setArr((yVal) * xComp + xVal, matrix.getArr((yVal - 1) * xComp + xVal));
						}
					}
					//sets the first row to zero as it will always be cleared i.e, set to zero
					for (int xVal = 1; xVal < xComp - 1; xVal++) {
						matrix.setArr((0) * xComp + xVal, 0);
					}

				}
				else {
					TetrisBlocksArr[matrix.getArr(i * xComp + j) - 1]->draw(window, j, i); 
				}
			}
		}
		//drawing the current block
		TetrisBlocksArr[currMino]->draw(window);
		
		//writng the score and other information on the window
		window.draw(gameTitle);

		scoreStr = "Score: " + to_string(score);
		scoreText.setString(scoreStr);
		window.draw(scoreText);

		levelStr = "Level: " + to_string(currentLevel);
		levelText.setString(levelStr);
		window.draw(levelText);

		lineStr = "Lines Cleared: " + to_string(noOfLinesCleared);
		lineText.setString(lineStr);
		window.draw(lineText);

		
		currentName.setString(str);
		window.draw(currentName);
	}


	bool update(Time deltaTime) {
		srand(time(NULL));

		//Game timing 
		speedCounter++;
		if (currentSpeed == speedCounter) {
			//force down one line at a time
			if (TetrisBlocksArr[currMino]->doesTetriminoFit(currXPos, TetrisBlocksArr[currMino]->refLocation.y + 1, TetrisBlocksArr[currMino]->currentRotationAngle, matrix)) {
				TetrisBlocksArr[currMino]->refLocation.y++;
			}			
			else {
				//lock the current piece into its position in the well
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						int rotationIndex = TetrisBlocksArr[currMino]->rotate(j, i);
						int wellIndex = (TetrisBlocksArr[currMino]->refLocation.y + i) * xComp + (TetrisBlocksArr[currMino]->refLocation.x + j);
						if (TetrisBlocksArr[currMino]->arr[rotationIndex] != 0) {
							matrix.setArr(wellIndex, TetrisBlocksArr[currMino]->getColor());
						}
					}
				}
				//check if horizontal lines formed and delete the line
				bool isLine;
				for (int yVal = 0; yVal < 4; yVal++) {
					if (TetrisBlocksArr[currMino]->refLocation.y + yVal < yComp - 1) { //-1 as the last cell is the boundary
					    isLine = true;
						for (int xVal = 1; xVal < xComp - 1; xVal++) {
							if (matrix.getArr(int(TetrisBlocksArr[currMino]->refLocation.y + yVal) * xComp + xVal) == 0) {
								isLine = false;
							}
						}
						//if the line present then show the animation to remove
						if (isLine) {
							for (int xVal = 1; xVal < xComp - 1; xVal++) {
								matrix.setArr(int(TetrisBlocksArr[currMino]->refLocation.y + yVal) * xComp + xVal, 8);
							}
							noOfLinesCleared++;
							linesCount++;
							score += 100;
						}
						if (linesCount == difficultyLevel ) {
							currentSpeed -= int(currentSpeed * 0.1); //increases speed by 10 percentage
							currentLevel++;
							if (currentLevel == 9) {
								currentLevel = 1;
								currentSpeed = 60;
							}
							linesCount = 0;
						}
					}
				}
				
				

				//choose the next piece
				TetrisBlocksArr[currMino]->initializeValues();
				currXPos = xComp / 2 - 1;
				currMino = rand() % 7;
				//if the new piece does not fit	
				gameOver = !(TetrisBlocksArr[currMino]->doesTetriminoFit(currXPos, TetrisBlocksArr[currMino]->refLocation.y, TetrisBlocksArr[currMino]->currentRotationAngle, matrix));
			}
			speedCounter = 0;
		}

		TetrisBlocksArr[currMino]->refLocation.x = currXPos;

		counter++;
		if (!isRightPressed && Keyboard::isKeyPressed(Keyboard::Right)) {
			if (TetrisBlocksArr[currMino]->doesTetriminoFit(currXPos + 1, TetrisBlocksArr[currMino]->refLocation.y, TetrisBlocksArr[currMino]->currentRotationAngle, matrix)) {
				TetrisBlocksArr[currMino]->refLocation.x = ++currXPos;
			}			
			isRightPressed = true;
		}
		else if (!isLeftPressed && Keyboard::isKeyPressed(Keyboard::Left)) {
			if (TetrisBlocksArr[currMino]->doesTetriminoFit(currXPos - 1, TetrisBlocksArr[currMino]->refLocation.y, TetrisBlocksArr[currMino]->currentRotationAngle, matrix)) {
				TetrisBlocksArr[currMino]->refLocation.x = --currXPos;
			}
			isLeftPressed = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down)) {
			if (TetrisBlocksArr[currMino]->doesTetriminoFit(currXPos, TetrisBlocksArr[currMino]->refLocation.y + 1, TetrisBlocksArr[currMino]->currentRotationAngle, matrix)) {
				TetrisBlocksArr[currMino]->refLocation.y += 1;
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up)) {
			if (!isRotatedHold && TetrisBlocksArr[currMino]->doesTetriminoFit(currXPos, TetrisBlocksArr[currMino]->refLocation.y, TetrisBlocksArr[currMino]->currentRotationAngle + 1, matrix)) {
				TetrisBlocksArr[currMino]->currentRotationAngle += 1;
				isRotatedHold = true;
			}
		}
		else {
			isRotatedHold = false;
		}

		//allows for only four movements per frame
		//else the block moves too rapidly
		//5 is the number of moves allowed per second
		if (counter >= currentSpeed/5) {
			isRightPressed = false;
			isLeftPressed = false;
			counter = 0;
		}

		return gameOver;
	}

	void setIsTextBoxOpen(bool flag) { isTextBoxOpen = flag; }

	bool getIsTextBoxOpen() { return isTextBoxOpen; }

	void getNameInput()
	{
		cin >> str;
		str = "Player: " + str;
	}

	void updateHighScore() {
		int i = 0;
		stringstream ss;
		int currentValue = stoi(highScoreArr[i][1]);

	    while ((currentValue > score) && i < 5) {
			cout << currentValue << endl;
	    	i++;
			currentValue = stoi(highScoreArr[i][1]);
	    }
		cout << "i: " << i << endl;
		if (i < 5) {
			//if a new high score is made
			for (int j = 3; j >= i; j--) {
				highScoreArr[j + 1][0] = highScoreArr[j][0];
				highScoreArr[j + 1][1] = highScoreArr[j][1];
			}
			highScoreArr[i][0] = str.substr(8,str.length()); //as the word "Player: " is added before it
			highScoreArr[i][1] = to_string(score);
			highScoresWrite.open("highScoreData.txt");
			for (int j = 0; j < 5; j++) {
				for (int k = 0; k < 2; k++) {
					highScoresWrite << highScoreArr[j][k] << endl;
				}
			}
			cout << "High Score updated!\n";
		}
		else {
			cout << "No new high score made!\n";
		}		
	}
};

