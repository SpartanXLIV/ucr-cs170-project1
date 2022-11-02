#ifndef EIGHT_PUZZLE_H
#define EIGHT_PUZZLE_H
#include <iostream> 
#include <map>	//DONT FORGET, IT'S IN THE TOY BOX
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
            empty = Calc_empty();
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


	void swap_right() 		//if movement of zero is possible, swap the positions!
        {
            if (empty.second != currPuzzle.size() - 1) //check if ur not on the edge 
            {
                string temp = currPuzzle.at(empty.first).at(empty.second + 1);
                currPuzzle.at(empty.first).at(empty.second + 1) = "0";
                currPuzzle.at(empty.first).at(empty.second) = temp;
                empty.second = empty.second + 1;
            }
        }
	void swap_left() 
        {
            if (empty.second != 0) //check if ur not on the edge 
            {
                string temp = currPuzzle.at(empty.first).at(empty.second - 1);
                currPuzzle.at(empty.first).at(empty.second - 1) = "0";
                currPuzzle.at(empty.first).at(empty.second) = temp;
                empty.second= empty.second - 1;
            }
        }
        void swap_down() 
        {
            if (empty.first != currPuzzle.size() - 1)  //check if ur not on the ceiling
            {
                string temp = currPuzzle.at(empty.first + 1).at(empty.second);
                currPuzzle.at(empty.first + 1).at(empty.second) = "0";
                currPuzzle.at(empty.first).at(empty.second) = temp;
                empty.first = empty.first + 1;
            }
        }
        void swap_up() 
        {
            if (empty.first != 0) 				//check if not on the floor
            {
                string temp = currPuzzle.at(empty.first - 1).at(empty.second);
                currPuzzle.at(empty.first - 1).at(empty.second) = "0";
                currPuzzle.at(empty.first).at(empty.second) = temp;
                empty.first = empty.first - 1;
            }
        }

//-------------------------------------------------------------------------------GREAT PUSH 1 10/29/22
        //helper functions
        int Get_g_cost() const //return g cost
        {
            return this->g_cost;
        }
        int Get_h_cost() const //return h cost
        {
            return this->h_cost;
        }
        vector<vector<string> > get_currPuzzle() const //return puzzle vector
        {
            return this->currPuzzle;
        }


        int MT_cost() 	//calculating the cost of misplaced tile using a map
        { //only checks to see if its the right tile, if not + 1
			vector<int> mt_map;
            int mt_cost = 0;
            for (int i = 0; i < currPuzzle.size(); i++) //convert to int so we can compare
            {
                for (int j = 0; j < currPuzzle.at(i).size(); j++) 	
                {
                    mt_map.push_back(stoi(currPuzzle.at(i).at(j))); //string to integer
                }
            }
            for (int i = 0; i < mt_map.size() - 1; i++) //checks if tile is wrong
            {
                if (mt_map.at(i) != i + 1) 
                {
                    mt_cost = mt_cost + 1;
                }
            }
            if (mt_map.at(mt_map.size() - 1) != 0) 
            {
                mt_cost = mt_cost + 1;
            }
            return mt_cost;
        }

        int MD_cost()  //calculating the cost on manhattan
        {
			int md_counter = 1;			//MD counter
            int md_cost = 0;	//md_cost
            
            
            for (int i = 0; i < currPuzzle.size(); i++) 
            {
                for (int j = 0; j < currPuzzle.at(i).size() && md_counter != currPuzzle.size() * currPuzzle.size(); j++) 
                {
                    if (currPuzzle.at(i).at(j) != to_string(md_counter)) 
                    {
                        for(int k = 0; k < currPuzzle.size(); k++) 
                        {
                            for (int l = 0; l < currPuzzle.at(k).size(); l++) 
                            {
                                if (to_string(md_counter) == currPuzzle.at(k).at(l)) 
                                {
                                    md_cost += abs(i - k) + abs(j - l);
                                }
                            }
                        }
                    }
                    md_counter++;
                }
            }
            if (currPuzzle.at(currPuzzle.size()-1).at(currPuzzle.size()-1) != "0") 
            {
                for (int i = 0; i < currPuzzle.size(); i++) 
                {
                    for (int j = 0; j < currPuzzle.size(); j++) 
                    {
                        if (currPuzzle.at(i).at(j) == "0") 
                        {
                            int sz = currPuzzle.size()-1;
                            md_cost += abs(sz - i) + abs(sz- j);
                        }
                    }
                }
            }
            return md_cost;
        }

        
        pair<int, int> Calc_empty() //finds and returns the empty/0 slot
        {
            for (int i = 0; i < currPuzzle.size(); i++) 		//going through rows
            {
                for(int j = 0; j < currPuzzle.at(i).size(); j++) //going through columns
                {
                    if (currPuzzle.at(i).at(j) == "0") 
                    {
                        pair<int, int> blank_rc(i, j);
                        return blank_rc;
                    }
                }
            }
            //if 0 could not be found, returns out of bounds
            pair<int, int> blank_rc(-1, -1);
            return blank_rc;
        }


        //these 4 will perform the actual operation and call the corresponding swap_up functions
        eight_puzzle Operate_right(eight_puzzle puzzle) 
        {
            puzzle.swap_right();
            return puzzle;
        }
        eight_puzzle Operate_left(eight_puzzle puzzle) 
        {
            puzzle.swap_left();
            return puzzle;
        }
        eight_puzzle Operate_down(eight_puzzle puzzle) 
        {
            puzzle.swap_down();
            return puzzle;
        }
        eight_puzzle Operate_up(eight_puzzle puzzle) 
        {
            puzzle.swap_up();
            return puzzle;
        }


        void Alg_cost(const int &alg) 		//check what algorithm the user selected
        {
            this->g_cost += 1;
            if (alg == 2) 
            {
                this->h_cost = MT_cost();
            }
            else if (alg == 3) 
            {
                this->h_cost = MD_cost();
            }
            else  //JUST IN CASE the while loop in main fails, algorithm will be set to UCS
            {
                this->h_cost = 0;
            }
        }

        void Print_cost() 
        {
			cout << "The best state to expand with a g(n) = " << g_cost << " and h(n) = " << h_cost << " is... " << endl;
        }
        
        bool operator<(const eight_puzzle &lhs) const // solves a declaration problem, we want to return the lowest value
        {
            return !((Get_g_cost() + Get_h_cost()) < (lhs.Get_g_cost() + lhs.Get_h_cost()));
        }
};

string mapToString(vector<vector<string> > state) //turns the 9 strings into 1 super string for comparison to goal
{
    string map_state;
    for (int i = 0; i < state.size(); i++) 
    {
        for (int j = 0; j < state.at(i).size(); j++) 
        {
            map_state.append(state.at(i).at(j));
        }
    }
    return map_state;
}

bool Goal_state(const eight_puzzle &puzzle) //compare the one string to check if it looks like this "0-9"
{
    string goal_string = "123456780";
    string curr_state = mapToString(puzzle.get_currPuzzle());
    if (curr_state == goal_string) 
    {
        return true;
    }
    return false;
}
//EXPAND YOUR MIND, OMORI!
void StateExpansion(eight_puzzle curr, priority_queue<eight_puzzle> &states, map<string, bool> &visited_states, const int &alg) //
{
    eight_puzzle puzzle_right = curr.Operate_right(curr); //keeps track if it can move in any direction
    eight_puzzle puzzle_left = curr.Operate_left(curr);
    eight_puzzle puzzle_down = curr.Operate_down(curr);
    eight_puzzle puzzle_up = curr.Operate_up(curr);

    visited_states[mapToString(curr.get_currPuzzle())] = 1;
    if (visited_states[mapToString(puzzle_up.get_currPuzzle())] == 0) 
    {
        puzzle_up.Alg_cost(alg);
        states.push(puzzle_up);	//prioritize based on f cost
    }
    if (visited_states[mapToString(puzzle_down.get_currPuzzle())] == 0) 
    {
        puzzle_down.Alg_cost(alg);
        states.push(puzzle_down);
    }
    if (visited_states[mapToString(puzzle_left.get_currPuzzle())] == 0) 
    {
        puzzle_left.Alg_cost(alg);
        states.push(puzzle_left);
    }
    if (visited_states[mapToString(puzzle_right.get_currPuzzle())] == 0) 
    {
        puzzle_right.Alg_cost(alg);
        states.push(puzzle_right);
    }
}


#endif
