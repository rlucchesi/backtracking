/*
You are given a 10X10 chessboard with a knight on coordinate (i, j). You have to find the number of blocks on the chessboard that the knight can be at in exactly n moves.

INPUT: will consist of three space seperated integers i, j, n where n is less than 10.

OUTPUT: Print a single integer denoting the number of blocks on the chessboard that the knight can be at in exactly n moves.

Problem Setter - Sheldon (https://www.hackerearth.com/@sheltauro)
*/

#include <iostream>
#include <string>
#include <deque>

class Knight {
public:
	const int BOARD_SIZE = 10;
	const int MAX_POSSIBLE_MOVES = 8;	// number of possible different moves a Knight can do

	Knight(int i, int j, int numMoves) {
		// output of the program
		this->numPlacedKnights = 0;
		// number of places the Knight can move
		this->numOfMoves = numMoves;
		// save original coordinates
		this->myI = i;
		this->myJ = j;
		
		// Construct the board game
		this->board = new int*[BOARD_SIZE];
		for (int row = 0; row < BOARD_SIZE; row++) {
			this->board[row] = new int[BOARD_SIZE];
			for (int col = 0; col < BOARD_SIZE; col++)
				this->board[row][col] = 0;
		}
	}

	// actually runs the solution
	int solve() {
		moveKnight(this->myI, this->myJ, 0);
		drawBoard();
		return this->numPlacedKnights;
	}

private:
	int** board;
	int numOfMoves;
	int numPlacedKnights;
	int myI;
	int myJ;

	void moveKnight(int i, int j, int index) {
		if (index >= this->numOfMoves)
			return;

		int ijToBePlaced, _i, _j;

		// load a local stack with possible moves
		std::deque<int> possibleMoves;
		loadDeque(i, j, possibleMoves);

		// while there are coordinates to be placed..
		while (!possibleMoves.empty()) {
			ijToBePlaced = possibleMoves.back();
			possibleMoves.pop_back();

			_i = ijToBePlaced / BOARD_SIZE;
			_j = ijToBePlaced % BOARD_SIZE;

			// place each coordinate 
			placeKnight(_i, _j);
			// recursive call to place the next move's coordinates
			if (_i >= 0 && _i < BOARD_SIZE && _j >= 0 && _j < BOARD_SIZE)
				moveKnight(_i, _j, index + 1);
		}
	}

	// place a knight in coordinate if it is within the board
	void placeKnight(int i, int j) {
		if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE) {
			if (this->board[i][j] == 0) {
				this->numPlacedKnights++;
				this->board[i][j] = 1;
			}
		}
	}

	// loads Deque with all possible moves
	void loadDeque(int i, int j, std::deque<int> &mydeque) {
		int _i, _j;
		_i = _j = 0;

		for (int k = 0; k < MAX_POSSIBLE_MOVES; k++) {
			switch (k) {
			case 0:
				_i = i - 2;
				_j = j - 1;
				break;
			case 1:
				_i = i - 2;
				_j = j + 1;
				break;
			case 2:
				_i = i - 1;
				_j = j + 2;
				break;
			case 3:
				_i = i + 1;
				_j = j + 2;
				break;
			case 4:
				_i = i + 2;
				_j = j + 1;
				break;
			case 5:
				_i = i + 2;
				_j = j - 1;
				break;
			case 6:
				_i = i + 1;
				_j = j - 2;
				break;
			default:
				_i = i - 1;
				_j = j - 2;
				break;
			}
			if (_i >= 0 && _j >= 0)
				mydeque.push_back(_i * BOARD_SIZE + _j);
		}
	}

	void drawBoard() {
		for (int row = 0; row < BOARD_SIZE; row++) {
			for (int col = 0; col < BOARD_SIZE; col++) {
				std::cout << std::to_string(this->board[row][col]) + " ";
			}
			std::cout << std::endl;
		}
	}
};


int main() {
	// Instantiate a Knight (coord i, coord j, number of moves) 	
	Knight a(0, 0, 2);
	std::cout << "Output: " + std::to_string(a.solve());
	std::cout << std::endl;

	system("pause");
	return 0;
}
