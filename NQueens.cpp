#include <iostream>
#include <string>

class NQueens {
public:
	// Constructor: setup the chess board
	NQueens(int n) {
		this->boardSize = n;
		this->board = new int*[this->boardSize];
		for (int row = 0; row < this->boardSize; row++) {
			this->board[row] = new int[this->boardSize];
			for (int col = 0; col < this->boardSize; col++) {
				this->board[row][col] = 0;
			}
		}
	}

	// starts the program and prints the result
	void solve() {
		if (placeQueens(0)) {
			for (int i = 0; i < this->boardSize; i++) {
				for (int j = 0; j < this->boardSize; j++) {
					std::cout << " " + std::to_string(this->board[i][j]);
				}
				std::cout << std::endl;
			}
		}
		else {
			std::cout << "NO SOLUTION EXISTS" << std::endl;
		}
	}

private:
	int** board;
	int boardSize;

	// will place the Queens one at a time, for column wise
	bool placeQueens(int queen) {
		//if we are here that means we have solved the problem
		if (queen == this->boardSize)
			return true;

		for (int row = 0; row < this->boardSize; row++) {
			// check if queen can be placed row,col
			if (canPlace(row, queen)) {
				// place the queen
				this->board[row][queen] = 1;

				// solve  for next queen (Recursive call)
				if (placeQueens(queen + 1))
					return true;

				// if we are here that means above placement didn't work
				// BACKTRACK
				this->board[row][queen] = 0;
			}
		}

		//if we are here that means we haven't found solution
		return false;
	}

	// check if queen can be placed at board[row][column]
	bool canPlace(int row, int col) {
		// check if no queen is placed in that particular row
		for (int i = 0; i < col; i++) {
			if (this->board[row][i] == 1)
				return false;
		}

		// check upper diagonal
		for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
			if (this->board[i][j] == 1)
				return false;
		}

		// check lower diagonal
		for (int i = row, j = col; i < this->boardSize && j >= 0; i++, j--) {
			if (this->board[i][j] == 1)
				return false;
		}

		return true;
	}
};


int main() {
	NQueens myQueenGame(4);
	myQueenGame.solve();
	system("pause");
}
