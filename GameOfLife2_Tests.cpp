#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>

#include "ErrorContext.h"
#include "GameOfLife2_Tests.h"

using std::cout;
using std::endl;
using std::setprecision;

using Testing::ErrorContext;
using csci2312::GameOfLife;
using csci2312::Cell;

#define DESC(x) desc(x, __LINE__)  // ugly hack, but saves some time


//  Test Cell constructor and destructor
void test_cell_smoketest(ErrorContext &ec) {
    bool pass;
    Cell* myCell;

    ec.DESC("Cell Default Constructor");
    pass = true;
    // Construct a Default Cell - state should be set to false
    myCell = new Cell;
    pass = (myCell->getState() == false);
    ec.result(pass);
    
    ec.DESC("Destruct Default Test Cell");
    // Cleans up after previous test, destruct the object
    delete myCell;
}

//  Test Cell setters and getters
void test_cell_setget(ErrorContext &ec) {
    bool pass;
    Cell* myCell;

    ec.DESC("Cell setState");
    pass = true;
    // Set the state of Cell, check face value has been set
    myCell = new Cell;
    pass = (myCell->setState(false), myCell->getFace() == csci2312::Cell::dead);
    pass = (myCell->setState(true), myCell->getFace() == csci2312::Cell::alive);
    ec.result(pass);
    
    ec.DESC("Destruct Default Test Cell");
    // Cleans up after previous test, destruct the object
    delete myCell;

    ec.DESC("Cell getState");
    pass = true;
    // Recall the state of Cell, default is false
    myCell = new Cell;
    pass = (myCell->getState() == false);
    ec.result(pass);
    
    ec.DESC("Destruct Default Test Cell");
    // Cleans up after previous test, destruct the object
    delete myCell;
    
    ec.DESC("Cell getFace");
    pass = true;
    // Recall the face value of Cell, default is dead
    myCell = new Cell;
    pass = (myCell->getFace() == csci2312::Cell::dead);
    ec.result(pass);
    
    ec.DESC("Destruct Default Test Cell");
    // Cleans up after previous test, destruct the object
    delete myCell;
}

//  Test GameOfLife constructor and destructor
void test_game_smoketest(ErrorContext &ec) {
    bool pass;
	GameOfLife* myGame;	

    ec.DESC("--- Test - GameOfLife - Smoketest ---");

    ec.DESC("GameOfLife Default Constructor");
    pass = true;  
        // Construct a Default GameOfLife - boardSize should be set to MAX_BOARD      
		myGame = new GameOfLife;              
		pass = (myGame->getBoardSize() == myGame->MAX_BOARD);  
        ec.result(pass);
	
	ec.DESC("Destruct Default Test Game");
        // Cleans up after previous test, destruct the object        
	    delete myGame;		   

	ec.DESC("Custom Constructor requesting a specific boad size");
	    pass = true;
	    // Construct a Custom GameOfLife - boardSize should be set to what was requested   
	    myGame = new GameOfLife(50);
	    pass = (myGame->getBoardSize() == 50);
	    ec.result(pass);
    
	ec.DESC("Destruct Custom Test Game");    
	   // Cleans up after previous test, destruct the object        
	   delete myGame;
        
}

// Game rules teat
void test_game_rules(ErrorContext &ec) {
    bool pass;
	GameOfLife *myGame;

    // Run at least once!!
    // assert(numRuns > 0);

    ec.DESC("--- Test - Game Rule 110  ---");
    	
	pass = true;
	// Construct a Default GameOfLife - boardSize should be set to MAX_BOARD      
	myGame = new GameOfLife;
    
	ec.DESC("--------- Alive cell with 2 alive neighbors  ---");
	pass = (myGame->executeRule110(2, true) == true);
	ec.result(pass);

	ec.DESC("--------- Alive cell with 3 alive neighbors  ---");
	pass = (myGame->executeRule110(3, true) == true);
	ec.result(pass);

    ec.DESC("--------- Dead cell with 3 alive neighbors  ---");
    pass = (myGame->executeRule110(3, false) == true);
    ec.result(pass);
    
    ec.DESC("--------- Alive cell with 1 alive neighbors  ---");
    pass = (myGame->executeRule110(1, true) == false);
    ec.result(pass);
    
    ec.DESC("--------- Alive cell with 0 alive neighbors  ---");
    pass = (myGame->executeRule110(0, true) == false);
    ec.result(pass);
    
    ec.DESC("--------- Alive cell with 4 alive neighbors  ---");
    pass = (myGame->executeRule110(4, true) == false);
    ec.result(pass);
    
    ec.DESC("--------- Alive cell with 5 alive neighbors  ---");
    pass = (myGame->executeRule110(5, true) == false);
    ec.result(pass);
    
    ec.DESC("--------- Alive cell with 6 alive neighbors  ---");
    pass = (myGame->executeRule110(6, true) == false);
    ec.result(pass);
    
    ec.DESC("--------- Alive cell with 7 alive neighbors  ---");
    pass = (myGame->executeRule110(7, true) == false);
    ec.result(pass);
    
    ec.DESC("--------- Alive cell with 8 alive neighbors  ---");
    pass = (myGame->executeRule110(8, true) == false);
    ec.result(pass);

	// Destruct the object at the end of test
	ec.DESC("Destruct Test Game");

    // Cleans up after previous test, destruct the object
	delete myGame;
}



