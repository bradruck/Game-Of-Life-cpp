// GameOfLife2_TestApp.cpp
#include <iostream>

#include "ErrorContext.h"
#include "GameOfLife2_Tests.h"

using std::cout;
using std::endl;

using namespace Testing;
using namespace csci2312;

int main() {

	ErrorContext ec(cout);

    cout << endl << "Testing PA2!!" << endl << endl;
        
	// Cell tests
	test_cell_smoketest(ec);

	test_cell_setget(ec);


    // GameOfLife tests
    test_game_smoketest(ec);

	test_game_rules(ec);

//	system("pause");

    return 0;
}
