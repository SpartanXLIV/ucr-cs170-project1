#include "eight_puzzle.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <utility> //will use later
#include <map>    //will use later


using namespace std;


void PrintState(eight_puzzle setPuzzle) 
{
    setPuzzle.Print_cost();
    setPuzzle.eight_puzzle::print_puzzle();
}

vector<string> Get_userPuzzle(string &userInput) //take the 3 rows and fill the 8 puzzle
{
    getline(cin, userInput);
    userInput.erase(remove(userInput.begin(), userInput.end(), ' '), userInput.end());
    vector<string> puzzleRow;
    for (unsigned i = 0; i < puzzle_rows; i++) 
    {
        puzzleRow.push_back(string(1, userInput.at(i)));
    }
    return puzzleRow;
}

int main() 
{
    vector<vector<string> > puzzleBoard;
    string userInput;
    bool makingPuzzle = true;
    while (makingPuzzle) 
    {
        cout << "Welcome to my 8-Puzzle Solver. Type '1' for default puzzle, or '2' to create your own. " << endl;
        cin >> userInput;
        if (userInput == "1") 
        {
            puzzleBoard = { {"1", "2", "3"},
                       {"4", "0", "6"},
                       {"7", "5", "8"} };
            makingPuzzle = false;	//exit while loop
        }
        else if (userInput == "2") 
        {
            cin.ignore();
            cout << "Enter your puzzle, using a zero to represent the blank. Please only enter valid 8-puzzles." << endl;
            cout << "Enter the puzzle demilimiting the numbers with a space. Type RETURN only when finished." << endl;
            cout << "Enter the first row: " << endl;
            puzzleBoard.push_back(Get_userPuzzle(userInput));
            cout << "Enter the second row: " << endl;
            puzzleBoard.push_back(Get_userPuzzle(userInput));
            cout << "Enter the third row: " << endl;
            puzzleBoard.push_back(Get_userPuzzle(userInput));
            makingPuzzle = false;	//exit while loop
        }
        else 
        {
            cout << "Invalid input! Please enter only '1' or '2'! " << endl;
            userInput.clear();
        }
    }

    int user_alg;
    
    cout << "Select algorithm. (1) for Uniform Cost Search (default), (2) for Misplaced Tile Heuristic, or (3) for Manhattan Distance Heuristic." << endl;
    cin >> user_alg; // else statement in SetCosts makes UCS the default JUST IN CASE
    
    while(user_alg < 1 || user_alg > 3)		//check to see only valid input is taken by user
    {
		cout << "Please only enter a valid number 1-3" << endl;
		cin >> user_alg;
	}
  return 0;
}
