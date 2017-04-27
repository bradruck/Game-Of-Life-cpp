//
//  GameOfLife2.cpp
//  CSCI 2312 - PA2
//
//  Created by Bradley Ruck on 9/21/16.
//  Copyright © 2016 Bradley Ruck. All rights reserved.
//

#include "GameOfLife2.h"

namespace csci2312 {
    using std::ostream;
    using std::istream;
    using std::ifstream;
    
    Cell::Cell() {
        state = false;
        face = dead;
    }
    
    Cell::Cell(bool state) {
        if (state)
            face = alive;
        else
            face = dead;
    }
    
    Cell::~Cell() {
        
    }
    
    bool Cell::getState() const {
        return state;
    }
    
    void Cell::setState(bool newState) {
        if (newState) {
            state = true;
            face = alive;
        }
        else {
            state = false;
            face = dead;
        }
    }
    
    char Cell::getFace() const {
        return face;
    }
    
    // Constructor
    GameOfLife::GameOfLife(size_t size) throw (bad_alloc) {
        try {
            boardSize = size;
            // Create the 2 dimensional dynamic array
            currentLife = new CellPtr[boardSize+2];
            for (int i = 0; i < boardSize+2; i++) {
                currentLife[i] = new Cell[boardSize+2];
            }
        // Warn if not enough dynamic memory space to create array
        } catch (bad_alloc) {
            std::cerr << "\nNot enough memory to create the Game Board.\n";
            exit(0);
        }
        // If memory allocation successful, seed the array with all dead cells, even outer border
        for (int r = 0; r < boardSize+2; r++) {
            for (int c = 0; c < boardSize+2; c++)
                currentLife[r][c].setState(false);
        }
    }
    
    // Copy Constructor
    GameOfLife::GameOfLife(const GameOfLife& game) {
        boardSize = game.boardSize;
        ruleSet = game.ruleSet;
        
        // Create a new 2 dimensional dynamic array
        currentLife = new CellPtr[boardSize + 2];
        for (int i = 0; i < boardSize + 2; i++) {
            currentLife[i] = new Cell[boardSize + 2];
        }
        // Copying the game currentLife board values to the newgame currentLife board
        for (int r = 0; r < boardSize + 2; r++) {
            for (int c = 0; c < boardSize + 2; c++) {
                currentLife[r][c] = game.currentLife[r][c].getState();
            }
        }
        std::cout << "The Copy Constructor was successful!\n\n";
    }
    
    // Destructor
    GameOfLife::~GameOfLife() {
        for (int i = 0; i < boardSize + 2; i++) {
            delete[] currentLife[i];
        }
        delete[] currentLife;
        currentLife = NULL;
    }
    
    // Sets the private member value for ruleSet - the playing rules selection choice
    void GameOfLife::setRuleSet(char choice) {
        ruleSet = choice;
    }
    
    // Returns private member value boardSize
    size_t GameOfLife::getBoardSize() const {
        return boardSize;
    }
    
    // Returns private member value ruleSet
    char GameOfLife::getRuleSet() const {
        return ruleSet;
    }
    
    // Implementation to seed the board from user input for number of seeds, then randomly locates seeds
    void GameOfLife::seedBoard(size_t seeds) {
        int count = 1, row, column;
        
        // Seeds placed randomly, but not on the outer border
        while (count <= seeds) {
            row = 1 + rand() % boardSize;
            column = 1 + rand() % boardSize;
            if (currentLife[row][column].getState() != true){
                currentLife[row][column].setState(true);
                count ++;
            }
        }
        
        // Verify that the board seed was successfull.
        std::cout << "\n**The board has been successfully seeded!**\n\n";
    }
    
    // Implementation to seed the board from an input text file
    void GameOfLife::seedBoard(string fileName) throw(FileIOException){
        ifstream infile;
        FileIOException fileProb("Error Opening File!\nCheck the name/path entered for accuracy and verify that it exits.");
        try {
            infile.open(fileName);
            if (infile) {
                if(infile >> *this)
                    std::cout << "\n**The board has been successfully seeded!**\n";
                return;
            }
            else
                throw fileProb;
        } catch (FileIOException fileProb) {
            fileProb.handleError();
            exit(0);
        }
    }
    
    // Executes Conway Set of Rules
    bool GameOfLife::executeRule110(unsigned int countAlive, bool currentState) {
        // Apply the rules for each cell based on the final alive count found in surroundNums, update nextLife board
        if (countAlive < 2 && currentState == true) // The cell dies
            return false;
        if (countAlive > 3 && currentState == true) // The cell dies
            return false;
        if (countAlive == 3 && currentState == false) // The cell is born
            return true;
        if (countAlive == 3 && currentState == true) // The cell stays alive
            return true;
        if (countAlive == 2 && currentState == true) // The cell stays alive
            return true;
        else
            return currentState;
    }
    
    // Executes Alternate Set of Rules known as 'High Life'
    bool GameOfLife::executeRuleHighLife(unsigned int countAlive, bool currentState) {
        // Apply the rules for each cell based on the final alive count found in surroundNums, update nextLife board
        if (countAlive < 2 && currentState == true) // The cell dies
            return false;
        if (countAlive > 3 && currentState == true) // The cell dies
            return false;
        if (countAlive == 3 && currentState == false) // The cell is born
            return true;
        if (countAlive == 3 && currentState == true) // The cell stays alive
            return true;
        if (countAlive == 2 && currentState == true) // The cell stays alive
            return true;
        // Extra rule added to original set
        if (countAlive == 6 && currentState == false) // The cell is born
            return true;
        else
            return currentState;
    }
    
    // Implement the game simulation for operator controlled, open-ended play
    void GameOfLife::run() {
        unsigned int gen = 1;
        char next;
        
        std::cout << "\n\nThis is the initial seed:\n";
        std::cout << *this;
        std::cout << "Please type a 'Y' to view the next generation or press 'N' to exit : ";
        std::cin >> next;
        while (next == 'y' || next == 'Y') {
            calculateNextGen(currentLife, nextLife);
            std::cout << "\nThis is generation number - " << gen << "\n";
            std::cout << *this;
            std::cout << "Please type a 'Y' to view the next generation or press 'N' to exit : ";
            std::cin >> next;
            gen++;
        }
    }
    
    // Implement the game simulation for defined incremented play
    void GameOfLife::run(unsigned int itr) {
        std::cout << "\n\nThis is the initial seed:\n";
        std::cout << *this;
        for(int gen = 0; gen < itr; gen++){
            calculateNextGen(currentLife, nextLife);
            std::cout << "\nThis is generation number - " << gen + 1 << "\n";
            std::cout << *this;
        }
        std::cout << "That was the final generation\n";
    }
    
    // Implements the next generation of the game board based on the game rules.
    void GameOfLife::calculateNextGen(CellPtr* currentLife, CellPtr* nextLife) {
        // Create a new board nextLife
        this->nextLife = new CellPtr[boardSize + 2];
        for (int i = 0; i < boardSize + 2; i++) {
            this->nextLife[i] = new Cell[boardSize + 2];
        }
        // Copying the currentLife board values to the nextLife board
        for (int r = 0; r < boardSize + 2; r++) {
            for (int c = 0; c < boardSize + 2; c++) {
                this->nextLife[r][c].setState(this->currentLife[r][c].getState());
            }
        }
        // Test each bordering cell for live or dead state. surroundNums increments for each live cell.
        unsigned int surroundNums = 0;
        for (int r = 1; r < boardSize + 1; r++) {
            for (int c = 1; c < boardSize + 1; c++) {
                if (this->currentLife[r-1][c-1].getState() == true)
                    surroundNums++;
                if (this->currentLife[r-1][c].getState() == true)
                    surroundNums++;
                if (this->currentLife[r-1][c+1].getState() == true)
                    surroundNums++;
                if (this->currentLife[r][c-1].getState() == true)
                    surroundNums++;
                if (this->currentLife[r][c+1].getState() == true)
                    surroundNums++;
                if (this->currentLife[r+1][c-1].getState() == true)
                    surroundNums++;
                if (this->currentLife[r+1][c].getState() == true)
                    surroundNums++;
                if (this->currentLife[r+1][c+1].getState() == true)
                    surroundNums++;
                switch(getRuleSet()) {
                        // The choice to play game with the Conway rules.
                    case 'A':
                    case 'a': {
                        this->nextLife[r][c].setState(executeRule110(surroundNums, this->currentLife[r][c].getState()));
                        break;
                    }
                        // The choice to play with the High Life rules.
                    case 'B':
                    case 'b': {
                        this->nextLife[r][c].setState(executeRuleHighLife(surroundNums, this->currentLife[r][c].getState()));
                        break;
                    }
                }
                surroundNums = 0; // reset the counter
            }
        }
        // Delete the old currentLife board pointers
        for (int i = 0; i < boardSize + 2; i++) {
            delete[] this->currentLife[i];
        }
        delete[] this->currentLife;
        
        this->currentLife = this->nextLife; // Change the curentLife array pointer to point to nextLife array
        
        this->nextLife = NULL;
    }
    
    // Overloaded operator for printing out the game board to the screen
    ostream& operator << (ostream& out, const GameOfLife& b) {
        size_t cols = b.boardSize + 2;
        size_t lines = b.boardSize + 2;
        
        for(int r = 1; r < lines - 1; r++) {
            for(int c = 1; c < cols - 1; c++) {
                out << b.currentLife[r][c].getFace() << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
        return out;
    }
    
    // Overloaded operator to input the board from a file
    istream& operator >> (istream& in, GameOfLife& b) {
        char status;
        
        // Read in the board input data, in the form of 1's and 0's.
        for (int r = 0; r < b.boardSize; r++) {
            for (int c = 0; c < b.boardSize; c++) {
                in.get(status);
                if (status == '1')
                    b.currentLife[r+1][c+1].setState(true);
                else if (status == '0')
                    b.currentLife[r+1][c+1].setState(false);
                else
                    in.ignore();
            }
        }
        return in;
    }
    
    // Error IOException to catch file reading errors
    FileIOException::FileIOException(string error_Message) {
        errorMessage = error_Message;
    }
    
    // Output the error message
    void FileIOException::handleError() {
        std::cout << std::endl << errorMessage << std::endl;
    }
}
