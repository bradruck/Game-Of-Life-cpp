//
//  GameOfLifeApp2.cpp
//  CSCI 2312 - PA2
//
//  Created by Bradley Ruck on 9/21/16.
//  Copyright © 2016 Bradley Ruck. All rights reserved.
//

#include "GameOfLife2.h"

using namespace csci2312;

void displayMainMenu();
void displayRunMenu();
void displayFileInputMenu();
void displayRulesSelectionMenu();

int main() {
    size_t size, seeds;
    unsigned int itr;
    int ch1, ch2;
    char choice1, choice2;
    string fileName;
    
    // Welcome message
    std::cout << "\nWelcome to the 'Game of Life', a cellular automaton - zero player\n  game, that was developed by British mathematician John Conway in 1970.\n    You will be asked to make certain selections to set-up the game framework.\n      The game will then run with minimal input from you. \n\nIf you are ready, let's start! \n\n";
    displayRulesSelectionMenu();
    std::cout << " Please make a selection (A or B) from the menu for the set\n of rules you would like to run: ";
    std::cin >> choice1;
    
    do {
        // Ensure that at least one set of rules is correctly selected.
        while (choice1 != 'A' && choice1 != 'a' && choice1 != 'B' && choice1 != 'b') {            std::cout << "\nThere was a problem with your selection.\nPlease reselect the rule set.\n";
            displayRulesSelectionMenu();
            std::cout << "Please make a selection (A or B): ";
            std::cin >> choice1;
        }
        // Display the set of rules that are currently running
        if (choice1 == 'A' || choice1 == 'a')
            std::cout << "\n\n   **Now running the 'Original Conway' set of rules.**\n";
        else if (choice1 == 'B' || choice1 == 'b')
            std::cout << "\n\n   **Now running the 'High Life' set of rules.**\n";
        
        displayMainMenu();
        // Check for non-integer selection.
        if (!(std::cin >> ch1)) {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "\nThat was not a valid choice!\n";
        }
        // Check for integer choice out-of-range.
        else if (ch1 < 1 || ch1 > 5)
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "\nThat was not a valid choice!\n";
        }
        // The three choices in the main menu.
        switch(ch1) {
            // First choice, to seed the game with a given board size and number of seeds, with randomized seed placement.
            case 1: {
                std::cout << "\nYou have chosen to seed the board randomly, \nPlease enter a board size (not to exceed " << csci2312::GameOfLife::MAX_BOARD << "): ";
                
                // Verify board size limitation.
                if (!(std::cin >> size) || size > csci2312::GameOfLife::MAX_BOARD) {
                    std::cout << "Your proposed size either exceeds the maximum allowable or was mis-typed!\n";
                    do{
                        std::cin.clear();
                        std::cin.ignore();
                        std::cout << "Please re-enter a board size (not to exceed " << csci2312::GameOfLife::MAX_BOARD << "): ";
                    } while (!(std::cin >> size) || size > csci2312::GameOfLife::MAX_BOARD);
                }
                // Create the instance of game for given board size.
                GameOfLife game(size);
                game.setRuleSet(choice1); // Set user's choice for game rules
                
                std::cout << "Please enter the number of random seeds: ";
                // Verify the number of random seeds for board, maximum is size x size.
                if (!(std::cin >> seeds) || seeds > size*size) {
                    std::cout << "\nThe number of seeds either exceeds the board capacity of " << size*size << "\n or was mis-typed.\n";
                    do{
                        std::cin.clear();
                        std::cin.ignore();
                        std::cout << "Please re-enter a seed size (not to exceed " << size*size << "): ";
                    } while (!(std::cin >> seeds) || seeds > size*size);
                }
                game.seedBoard(seeds);
                // Display the menu to play the game.
                displayRunMenu();
                std::cout << "\nPlease enter either A or B: ";
                std::cin >> choice2;
                if (choice2 == 'A' || choice2 == 'a' || choice2 == 'B' || choice2 == 'b') {
                    // The two choices for the simulations menu for playing the game.
                    switch(choice2) {
                        // The choice to play open-ended with the user deciding when to stop.
                        case 'A':
                        case 'a': {
                            std::cout << "\nYou have chosen to run the simulation open-ended.\n";
                            game.run();
                            break;
                        }
                        // The choice to play with a preselected number of generations.
                        case 'B':
                        case 'b': {
                            std::cout << "\nYou have chosen to run the simulation with specified generations.\nPlease enter the number of generations to run: ";
                            std::cin >> itr;
                            game.run(itr);
                            break;
                        }
                    }
                }
                break;
            }
            // Second choice to seed the game from an initialization text file.
            case 2: {
                std::cout << "\nYou have chosen to seed the board from an input file.\n";
                displayFileInputMenu();
                std::cout << "\nPlease enter either 1 or 2: ";
                std::cin >> ch2;
                // The two choices in the file select menu, either a user defined file name, or a provided test file.
                switch (ch2) {
                    // First choice to read from user entered file
                    case 1: {
                        std::cout << "\nPlease enter a file name: ";
                        std::cin >> fileName;
                        std::ifstream infile;
                        
                        infile.open(fileName);
                        
                        // First line of file holds the board size.
                        infile >> size;
                        infile.ignore();
                        
                        if (size > GameOfLife::MAX_BOARD) {
                            std::cout << "\nYour file board size exceeds the maximum allowable - " << GameOfLife::MAX_BOARD << "!\n";
                            exit(0);
                        }
                        // Create the instance of game for given board size.
                        GameOfLife game(size);
                        game.setRuleSet(choice1); // Set user's choice for game rules
                        game.seedBoard(fileName);
                        infile.close();
                        
                        // Display the menu to play the game.
                        displayRunMenu();
                        std::cout << "\nPlease enter either A or B: ";
                        std::cin >> choice2;
                        if (choice2 == 'A' || choice2 == 'a' || choice2 == 'B' || choice2 == 'b') {
                            // The two choices for the simulations menu for playing the game.
                            switch(choice2) {
                                // The choice to play open-ended with the user deciding when to stop.
                                case 'A':
                                case 'a': {
                                    std::cout << "\nYou have chosen to run the simulation open-ended.\n";
                                    game.run();
                                    break;
                                }
                                // The choice to play with a preselected number of generations.
                                case 'B':
                                case 'b': {
                                    std::cout << "\nYou have chosen to run the simulation with specified generations.\nPlease enter the number of generations to run: ";
                                    std::cin >> itr;
                                    game.run(itr);
                                    break;
                                }
                            }
                        }
                        break;
                    }
                    // Second choice to read from a provided test file
                    case 2: {
                        std::cout << "\nThe test file is named 'SeedPattern2.txt'\n";
                        fileName = "SeedPattern2.txt"; // test file name
                        std::ifstream infile;
                        
                        infile.open(fileName);
                        // First line of file holds the board size.
                        infile >> size;
                        infile.ignore();
                        
                        if (size > GameOfLife::MAX_BOARD) {
                            std::cout << "\nYour file board size exceeds the maximum allowable - " << GameOfLife::MAX_BOARD << "!\n";
                            exit(0);
                        }
                        // Create the instance of game for given board size.
                        GameOfLife game(size);
                        game.setRuleSet(choice1); // Set user's choice for game rules
                        game.seedBoard(fileName);
                        infile.close();
                        
                        // Display the menu to play the game.
                        displayRunMenu();
                        std::cout << "\nPlease enter either A or B: ";
                        std::cin >> choice2;
                        if (choice2 == 'A' || choice2 == 'a' || choice2 == 'B' || choice2 == 'b') {
                            // The two choices for the simulations menu for playing the game.
                            switch(choice2) {
                                // The choice to play open-ended with the user deciding when to stop.
                                case 'A':
                                case 'a': {
                                    std::cout << "\nYou have chosen to run the simulation open-ended.\n";
                                    game.run();
                                    break;
                                }
                                // The choice to play with a preselected number of generations.
                                case 'B':
                                case 'b': {
                                    std::cout << "\nYou have chosen to run the simulation with specified generations.\nPlease enter the number of generations to run: ";
                                    std::cin >> itr;
                                    game.run(itr);
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
                break;
            }
            // Third choice to reset the game rules
            case 3: {
                std::cout << "\nYou have chosen to change the rule set.\n";
                std::cout << "\n   **The game is currently running the ";
                if (choice1 == 'A' || choice1 == 'a')
                    std::cout << "'Original Conway'";
                else
                    std::cout << "'High Life'";
                std::cout << " set of rules.**\n\n";
                displayRulesSelectionMenu();
                std::cout << "\nPlease make a selection (A or B) from the menu for the set\nof rules you would like to run: ";
                std::cin >> choice1;
                break;
            }
            // Fourth choice to verify the copy constructor using the test file to create an original game board
            case 4: {
                fileName = "SeedPattern2.txt"; // test file name
                
                std::cout << "\n\nNow Testing the Copy Constructor\n\n";
                
                // Create and display an original game from the test file
                std::ifstream infile;
                infile.open(fileName);
                infile >> size; // First line of file holds the board size.
                infile.ignore();
                GameOfLife game(size); // Create a game from test file
                game.seedBoard(fileName); // Seed game board from test file
                infile.close();
                std::cout << "\nThis is the initial game board from the test file\n";
                std::cout << game;
                std::cout << "This is the original game board size: " << game.getBoardSize() << "\n\n\n";
                std::cout << game.getRuleSet();
                
                // Create a duplicate game using copy constructor and display
                GameOfLife newgame(game); // Call copy constructor
                std::cout << "\nThis is the initial game board from the new game\n";
                std::cout << newgame;
                std::cout << "This is the new game board size: " << newgame.getBoardSize() << "\n\n\n";
                break;
            }
            // Final choice to exit the program.
            case 5: {
                std::cout << "\n**You have chosen to exit the program.**\n\n Goodbye!\n\n\n";
                break;
            }
        }
    } while (ch1 != 5);
    
    return 0;
}

// Four different menus.
void displayMainMenu(){
    std::cout << "\n           MAIN MENU\n";
    std::cout << "_____________________________________\n\n";
    std::cout << "1)  Seed the board randomly\n";
    std::cout << "2)  Seed the board from an input file\n";
    std::cout << "3)  Change the rule set\n";
    std::cout << "4)  Test the copy constructor\n";
    std::cout << "5)  Exit the program\n";
    std::cout << "\nEnter your choice: ";
}

void displayRunMenu(){
    std::cout << "\n                    SIMULATION MENU\n";
    std::cout << "___________________________________________________________\n\n";
    std::cout << "A)  Run the simulation open-ended\n";
    std::cout << "B)  Run the simlation for a specified number of generations\n";
    std::cout << "\n";
}

void displayFileInputMenu(){
    std::cout << "\n    FILE INPUT MENU\n";
    std::cout << "___________________________\n\n";
    std::cout << "1)  Enter you own file name\n";
    std::cout << "2)  Run the test file\n";
    std::cout << "\n";
}

void displayRulesSelectionMenu(){
    std::cout << "\n                RULES SELECTION MENU\n";
    std::cout << "________________________________________________________\n\n";
    std::cout << "A)  Run the game with the original 'Conway' rules\n";
    std::cout << "B)  Run the game with 'High Life' rules\n";
    std::cout << "\n";
}
