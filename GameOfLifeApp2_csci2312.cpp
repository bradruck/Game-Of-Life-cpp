// *********************************************************************
//  This program demostrates the Game Of Life 
//  
// *********************************************************************


#include <iostream>
#include <cstdlib>
#include <string>

#include "GameOfLife2_csci2312.h"

using std::cout;
using std::endl;
using std::cin;
using namespace csci2312;


// ======================
//     main function
// ======================
int main()

{
	GameOfLife* myGame;

    // Construct the game anticipating memory allocation issues
	try {
		
		myGame = new GameOfLife(20);
	}
	catch (std::bad_alloc) {
		cout << "Failed to allocate memory for a new game" << endl;

        system("pause");
		return(1);
	};

	////////// STUDENT TASK - go on with your menus etc
	


    ///////// END TASK

	delete myGame;  // invokes GameOfLife destructor 

	return 0;
}

