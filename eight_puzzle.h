#ifndef EIGHT_PUZZLE_H
#define EIGHT_PUZZLE_H
#include <iostream> //DONT FORGET, IT'S IN THE TOY BOX
#include <vector>
#include <queue>


using namespace std;

const unsigned int puzzle_rows = 3;	//THREE ROWS FOR 8 PUZZLE

class eight_puzzle 
{
    private:
        vector<vector<string> > currPuzzle;
        unsigned int g_cost;
        unsigned int h_cost;
        pair<int, int> empty;	//pair idea given from cs130
        
    public:
        eight_puzzle() 			//empty constructor
        {
            g_cost = 0;
            h_cost = 0;
            empty = make_pair(0, 0);
        }

        eight_puzzle(vector<vector<string> > puzzle) //constructor
        {
            this->currPuzzle = puzzle;
            g_cost = 0;
            h_cost = 0;
            empty = CalcBlank();
        }

        void print_puzzle() 					//prints out 9 values in 3 rows, or the 3x3 puzzle
        {
            for (int i = 0; i < currPuzzle.size(); i++) 
            {
                for (int j = 0; j < currPuzzle.at(i).size(); j++) 
                {
                    cout << currPuzzle.at(i).at(j) << " ";	//cout's the row
                }
                cout << endl;		//end of row
            }
        }


		bool valid_right() 			//these 4 will check if 0 is present first so that a swap could be made
        {
            if (empty.second == currPuzzle.size() - 1) 
            {
                return false;
            }
            return true;
        }
		bool valid_left() 
        {
            if (empty.second == 0) 
            {
                return false;
            }
            return true;
        }
        bool valid_down() 
        {
            if (empty.first == currPuzzle.size() - 1) 
            {
                return false;
            }
            return true;
        }
        bool valid_up() 		
        {
            if (empty.first == 0) 
            {
                return false;
            }
           return true;
        }


		void swap_right() 		//and if movement of zero is possible, swap the positions!
        {
            if (valid_right()) 
            {
                string temp = currPuzzle.at(empty.first).at(empty.second + 1);
                currPuzzle.at(empty.first).at(empty.second + 1) = "0";
                currPuzzle.at(empty.first).at(empty.second) = temp;
                empty.second = empty.second + 1;
            }
        }
		void swap_left() 
        {
            if (valid_left()) 
            {
                string temp = currPuzzle.at(empty.first).at(empty.second - 1);
                currPuzzle.at(empty.first).at(empty.second - 1) = "0";
                currPuzzle.at(empty.first).at(empty.second) = temp;
                empty.second= empty.second - 1;
            }
        }
        void swap_down() 
        {
            if (valid_down()) 
            {
                string temp = currPuzzle.at(empty.first + 1).at(empty.second);
                currPuzzle.at(empty.first + 1).at(empty.second) = "0";
                currPuzzle.at(empty.first).at(empty.second) = temp;
                empty.first = empty.first + 1;
            }
        }
        void swap_up() 
        {
            if (valid_up()) 
            {
                string temp = currPuzzle.at(empty.first - 1).at(empty.second);
                currPuzzle.at(empty.first - 1).at(empty.second) = "0";
                currPuzzle.at(empty.first).at(empty.second) = temp;
                empty.first = empty.first - 1;
            }
        }

};
