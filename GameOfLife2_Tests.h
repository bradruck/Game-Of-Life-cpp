
#ifndef GameOfLife2_Tests_h
#define GameOfLife2_Tests_h

#include "GameOfLife2.h"
#include "ErrorContext.h"

using Testing::ErrorContext;


// - - - - - - - - - Tests: class Cell - - - - - - - - - -

// Smoke test
void test_cell_smoketest(ErrorContext &ec);

// Cell set/get test
void test_cell_setget(ErrorContext &ec);

// - - - - - - - - - Tests: class GameOfLife - - - - - - - - - -

// Smoke test
void test_game_smoketest(ErrorContext &ec);

// Rules test
void test_game_rules(ErrorContext &ec);

#endif /* GameOfLife2_Tests_h */
