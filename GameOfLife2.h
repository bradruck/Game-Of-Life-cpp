//
//  GameOfLife2.h
//  CSCI 2312 - PA2
//
//  Created by Bradley Ruck on 9/21/16.
//  Copyright © 2016 Bradley Ruck. All rights reserved.
//

#ifndef GameOfLife2_h
#define GameOfLife2_h

#include <iostream>  // Provides ostream
#include <fstream>   // Provides ifstream
#include <string>    // String operations
#include <cstdlib>   // Randomizer

namespace csci2312 {
    using std::string;
    using std::istream;
    using std::ostream;
    
    // PA2: standard exception if memory allcation failed
    using std::bad_alloc;
    
    // Class Cell stays the same for PA2
    class Cell {
        
    public:
        static const char alive ='o';   // alive image
        static const char dead = '-';   // dead image
        
        Cell(); // default constructor
        Cell(bool cellState);
        ~Cell(); // destructor
        
        bool getState() const;
        char getFace() const;
        
        void setState(bool newState);
        
    private:
        bool state=false;
        char face;
    };
    
    // PA2: File IO Error custom exception  class
    class FileIOException {
        
    public:
        FileIOException(string error_Message);
        void handleError();
                
    private:
        string errorMessage;
    };
    
    // PA2: Class GameOfLife will have some new and some changed features
    class GameOfLife {
        
    public:
        
        // PA2: default display board size
        static const unsigned int MAX_BOARD = 30;
        
        // PA2: New type (pointer to Cell type) handy with dynamic arrays
        typedef Cell* CellPtr;
        
        // PA2: Constructs the board of the requested size, can throw exception.
        // If parameter is omitted, it becomes the default constructor, and the board will have MAX_BOARD size
        GameOfLife(size_t boardSize = MAX_BOARD) throw (bad_alloc);
        
        // PA2:  Copy-constructor creates a new instance as a deep copy of the referenced object
        GameOfLife(const GameOfLife& game);
        
        // PA2:  destructor must release memory taken by dynamic arrays
        ~GameOfLife(); // destructor
        
        // Sets the value for the set of rules to play by
        void setRuleSet(char);
        
        // Returns board size
        size_t getBoardSize() const;
        
        // Returns rule set
        char getRuleSet() const;
        
        // PA2: seeds the board from a file and throws an exception if there was trouble with file
        void seedBoard(string fileName) throw (FileIOException);
        
        // PA2: seeds the  board with a given number of seeds at randomized locations
        void seedBoard(size_t seeds);
        
        // PA2:  Executes Conway set of rules (same rules as PA1). Returns next state
        // Needed for TASK #5 to develop a test harness (the files test harness will be provided separately)
        bool executeRule110(unsigned int countAlive, bool currentState);
        
        // PA2:  Executes additional set of rules. Returns next state
        bool executeRuleHighLife(unsigned int countAlive, bool currentState);
        
        // PA2:
        void run();
        void run(unsigned int numberOfIterations);
        
        friend ostream& operator << (ostream& out, const GameOfLife& board);
        
        // PA2:  overloaded input operator to input the board (from file of keyboard)
        friend istream& operator >> (istream& in, GameOfLife& board);
        
    private:
        
        // PA2:  Encapsulate next generation calculation in a methos.  Needed only for OPTIONAL Task #6
        void calculateNextGen(CellPtr* current, CellPtr* next);
        
        // PA2:  dynamic arrays of Cells. New type CellPtr defined (typedef Cell* CellPtr)
        // currentLife and and nextLife are handles to the dynamic arrays
        CellPtr *currentLife;
        CellPtr *nextLife;
        
        // Just an example how to declare variable cl as a handle to our array of Cells.  Not needed to satisfy PAs
        // The accessor method getCurrentLife() above uses the same syntax for the return type
        // PA2 with dynamic arrays: const CellPtr* cl = currentLife; Cell currentLife[MAX_BOARD + 2][MAX_BOARD + 2];
        
        char ruleSet; // Rule set option under which to run the game
        
        size_t boardSize;       // Board size requested in the constructor
        
        // PA2: A handle to the array that needs to be displyed next.  Only needed for OPTIONAL TASK #6
        CellPtr *displayBoard;
    };
}

#endif /* GameOfLife2_h */
