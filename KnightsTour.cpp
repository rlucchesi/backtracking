#include <iostream>
#include <string>

class KnightsTour {
public:
	const int BOARD_SIZE = 8;
	const int SPOTS = BOARD_SIZE * BOARD_SIZE;

	KnightsTour(int i, int j) {
		// number of placed Knights
		this->counter = 0;
		// save original coordinates
		this->initialI = i;
		this->initialJ = j;

		// Construct the board game
		this->board = new int*[BOARD_SIZE];
		for (int row = 0; row < BOARD_SIZE; row++) {
			this->board[row] = new int[BOARD_SIZE];
			for (int col = 0; col < BOARD_SIZE; col++) {
				if (row == i && col == j)
					this->board[row][col] = ++this->counter;
				else
					this->board[row][col] = 0;
			}
		}
	}
	
	// actually runs the solution
	void run() {
		if (placeKnight(this->initialI, this->initialJ))
			drawBoard();
		else
			std::cout << "Failed to place all Knights" << std::endl;
	}

private:
	int** board;
	int counter, initialI, initialJ;

	static int const MAX_NUM_MOVES = 8;

	int moveI[MAX_NUM_MOVES] = { 1, 2,  2,  1, -1, -2, -2, -1 };
	int moveJ[MAX_NUM_MOVES] = { 2, 1, -1, -2, -2, -1,  1,  2 };

	// place a knight in a i,j position on the game board
	bool placeKnight(int i, int j) {
		//std::cout << this->counter << std::endl;
		if (this->counter == SPOTS)
			return true;

		// hold current coordinates
		int _i, _j;

		// traverse all possible moves
		for (int k = 0; k < MAX_NUM_MOVES; k++) {
			_i = i + moveI[k];
			_j = j + moveJ[k];

			if (canBePlacedAt(_i, _j)) {
				this->board[_i][_j] = ++this->counter;

				// recursive call for the next move
				if (placeKnight(_i, _j))
					return true;

				// backtracking (if necessary)
				this->board[_i][_j] = 0;
				this->counter--;
			}
		}
		return false;
	}

	// check if a knight can be place in a i,j coordinate
	bool canBePlacedAt(int i, int j) {
		if (i < 0 || i >= BOARD_SIZE || j < 0 || j >= BOARD_SIZE || this->board[i][j] != 0)
			return false;

		return true;
	}

	// draw the board (display the result)
	void drawBoard() {
		for (int row = 0; row < BOARD_SIZE; row++) {
			for (int col = 0; col < BOARD_SIZE; col++) {
				std::cout << std::to_string(this->board[row][col]) + "\t";
			}
			std::cout << std::endl;
		}
	}
};

int main() {
	KnightsTour a(0, 0);
	a.run();
	
	system("pause");
	return 0;
}

