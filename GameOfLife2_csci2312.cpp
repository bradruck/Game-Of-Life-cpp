#include "GameOfLife2_csci2312.h"

using std::cout;
using std::endl;

namespace csci2312

{

	Cell::Cell() {
		// to do		
	};

	Cell::Cell(bool cellState) {
		// to do
	}

	Cell::~Cell() {};

	bool Cell::getState() const {
		// to do

        // mockup to comply with the return type
		return true;
	}
	
	void Cell::setState(bool newState) {
		// to do
	}

	char Cell::getFace() const {
		// to do

		// mockup to comply with the return type
		return 0;
	}
    	

	GameOfLife::GameOfLife(size_t myBoardSize) throw (std::bad_alloc) {

		// todo
		
        // To test the exception, then remove
		// throw (std::bad_alloc());
	}

	GameOfLife::~GameOfLife() {
		
		// to do

		cout << "Object desctructed \n";
	};

	
	size_t GameOfLife::getBoardSize() const {

		// to do

		// mockup to comply with the return type
		return 0;
		
    }

	void GameOfLife::seedBoard(string fileName)  throw (FileIOException) {

         // to do
		
	}
		
		
	void GameOfLife::seedBoard(size_t seeds) {
         // to do
	}

	void GameOfLife::run() {
	     // to do
	}

	bool GameOfLife::executeRule110(unsigned int countAlive, bool currentState) {
		// to do

		// mockup to comply with the return type
		return !currentState;
	}

	bool GameOfLife::executeRuleXXX(unsigned int countAlive, bool currentState) {

        // to do

		// mockup to comply with the return type
		return !currentState;
	}
	
	void GameOfLife::calculateNextGen(CellPtr* current, CellPtr* next) {
        
        // to do

	}

	void GameOfLife::run(unsigned int numberOfIterations) {
		 // to do

	}

	//  Display cell's face 
	ostream& operator << (ostream& out, const Cell& cell) {
		out << (cell.getState() ? cell.alive : cell.dead);
		return out;
	}

	//  Display game's board 
	ostream& operator << (ostream& out, const GameOfLife& board) {
    
    	// Iterate over the board and display cells
		for (unsigned int row = 1;  row <= board.boardSize; row++) {
			for (unsigned int column = 1; column <= board.boardSize; column++) {				
				// Same as in PA1 - current board always has the latest state
                out << board.currentLife[row][column];

                // PA2 Optional #6 - assumes that displayBoard points to the latest
                // displayBoard needs to be maintained in thbe run method

                // out << board.displayBoard[row][column];
			}
			out << endl;
		}
		return out;
	}	
}


