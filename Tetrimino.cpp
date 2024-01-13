#include "Tetrimino.h"

Tetrimino::Tetrimino()
{
	refLocation.x = 0;
	refLocation.y = 0;
	currentRotationAngle = 0;
	if (!texture.loadFromFile("Blocks.jpg")) {
		cout << "Error!\n";
	}
	mino.setTexture(texture);
}

void Tetrimino::draw(RenderWindow& window)
{
	for (int i = 0; i < Rows; i++) {
		for (int j = 0; j < Columns; j++) {
			if (arr[rotate(j, i)] == color) {
				mino.setPosition((refLocation.x + j) * CellSize, (refLocation.y + i) * CellSize);
				window.draw(mino);
			}
		}
	}
}

void Tetrimino::draw(RenderWindow& window, int x, int y)
{
	mino.setPosition(x * CellSize, y * CellSize);
	window.draw(mino);
}

//returns the index of the tetramino cell after rotation
//used where a check needs to be made if the rotation is possible or not
int Tetrimino::rotate(int rotationNum, int x, int y)
{
	switch (rotationNum % 4)
	{
	case 0: 
		return (y * Columns) + x; //for 0 degrees
		break;
	case 1:
		return (12 + y - Columns * x); //for 90 degrees
		break;
	case 2:
		return (15 - x - y * Columns); //for 180 degrees
		break;
	case 3:
		return (3 - y + (Columns * x)); //for 270 degrees
		break;
	default:
		break;
	}
	return 0;
}

//used where the current state of tetrimino is required
int Tetrimino::rotate(int x, int y)
{
	switch (currentRotationAngle % 4)
	{
	case 0:
		return (y * Columns) + x; //for 0 degrees
		break;
	case 1:
		return (12 + y - Columns * x); //for 90 degrees
		break;
	case 2:
		return (15 - x - y * Columns); //for 180 degrees
		break;
	case 3:
		return (3 - y + (Columns * x)); //for 270 degrees
		break;
	default:
		break;
	}
	return 0;
}

int Tetrimino::getColor()
{
	return color;
}

bool Tetrimino::doesTetriminoFit(int currX, int currY, int rotationNum, Well matrix)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int rotationIndex = rotate(rotationNum, j, i);
			int wellIndex = (currY + i) * xComp + (currX + j);
			//boundary checks
			if (currY + i >= 0 && currY + i < yComp) {
				if (currX + j >= 0 && currX + j < xComp) {
					if (arr[rotationIndex] == getColor() && matrix.getArr(wellIndex) != 0) {
						//collsion if non zero elements present in the well
						return false;
					}
				}
			}
		}
	}
	return true;
}

void Tetrimino::initializeValues()
{
	refLocation.x = 0;
	refLocation.y = 0;
	currentRotationAngle = 0;
}


I::I()
{
	mino.setTextureRect(IntRect(0, 0, CellSize, CellSize));
	color = 1;
	//Initializing the I block
	arr[2] = color;
	arr[6] = color;
	arr[10] = color;
	arr[14] = color;
}

J::J()
{
	mino.setTextureRect(IntRect(28, 0, CellSize, CellSize));
	color = 2;
	//Initializing the J block
	arr[2] = color;
	arr[6] = color;
	arr[10] = color;
	arr[9] = color;
}

L::L()
{
	mino.setTextureRect(IntRect(56, 0, CellSize, CellSize));
	color = 3;
	//Initializing the L block
	arr[1] = color;
	arr[5] = color;
	arr[9] = color;
	arr[10] = color;
}

S::S()
{
	mino.setTextureRect(IntRect(84, 0, CellSize, CellSize));
	color = 4;
	//Initializing the S block
	arr[1] = color;
	arr[5] = color;
	arr[6] = color;
	arr[10] = color;
}

O::O()
{
	mino.setTextureRect(IntRect(112, 0, CellSize, CellSize));
	color = 5;
	//Initializing the O block
	arr[5] = color;
	arr[6] = color;
	arr[9] = color;
	arr[10] = color;
}

T::T()
{
	mino.setTextureRect(IntRect(140, 0, CellSize, CellSize));
	color = 6;
	//Initializing the T block
	arr[1] = color;
	arr[5] = color;
	arr[9] = color;
	arr[6] = color;
}

Z::Z()
{
	mino.setTextureRect(IntRect(168, 0, CellSize, CellSize));
	color = 7;
	//Initializing the Z block
	arr[2] = color;
	arr[6] = color;
	arr[5] = color;
	arr[9] = color;
}