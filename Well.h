#pragma once
#define xComp 12
#define yComp 21

class Well {
private:
	int arr[yComp * xComp];

public:
	Well() {
		for (int i = 0; i < yComp; i++) {
			for (int j = 0; j < xComp; j++) {
				arr[i * xComp + j] = (j == 0 || i == yComp - 1 || j == xComp - 1) ? 9 : 0;
				//stores 9 in the boundaries
			}
		}
	}
	void setArr(int index, int value) {
		arr[index] = value;
	}
	int getArr(int index) {
		return arr[index];
	}
};