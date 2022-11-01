#include "eight_puzzle.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <map>


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

    eight_puzzle setPuzzle(puzzleBoard);
    priority_queue<eight_puzzle> states;
    map<string, bool> visitedStates;
    states.push(setPuzzle);
    
    int queueSizeMAX = states.size();
    int nodesExpanded = 0;	//used to count number of nodes expanded
    
    while(!states.empty()) 						//fillup
    {
        if (queueSizeMAX < states.size()) 
        {
            queueSizeMAX = states.size();
        }
        eight_puzzle currState = states.top();
        states.pop();
        if (Goal_state(currState)) //check if current state is == goal state
        {
            PrintState(currState);
            cout << endl << "Goal state!" << endl << endl;
            cout << "Solution depth was " << currState.Get_g_cost() << endl;
            cout << "Number of nodes expanded: " << nodesExpanded << endl;
            cout << "Max queue size: " << queueSizeMAX << endl;
            return 0;
        }
 
        PrintState(currState);
        StateExpansion(currState, states, visitedStates, user_alg);
        nodesExpanded++;
    }
    
    cout << "No possuble solution found!" << endl;	//usually if the puzzle is impossible to solve
    cout << "Number of nodes expanded: " << nodesExpanded << endl;
    cout << "Max queue size: " << queueSizeMAX << endl;
    
    return 0;
}
