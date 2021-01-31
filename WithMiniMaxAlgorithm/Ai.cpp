#include <iostream>
#include "Ai.hpp"

namespace mro {
	Ai::Ai() {}

	bool Ai::win(std::vector<int>& win, std::vector<int>& lose, std::vector<int>& vv) {
		bool a = win.size() + win.size() == vv.size();
		bool b = std::accumulate(win.begin(), win.end(), 0) < std::accumulate(lose.begin(), lose.end(), 0);
		if(a && b)
			return true;
		else
			return false;
	}

	bool Ai::tie(std::vector<int>& vai, std::vector<int>& vheu, std::vector<int>& vv) {
		if(win(vai, vheu, vv))
			return false;
		bool a = ((vai.size() + vheu.size()) == vv.size());
		if(a)
			return true;
		return false;
	}

	Move Ai::minimax(std::vector<int>& vai, std::vector<int>& vheu, std::vector<int>& vv, std::vector<int>::iterator& itBegvv, std::vector<int>::iterator& itEndvv, bool maximizing_player) {
		Move best_move;
		bool side = true;
		if(win(vai, vheu, vv) || win(vheu, vai, vv)) {
			// If maximizing_player wins we can return -1
			//		and if maximizing_player loses we
			//		returns 1;
			if(win(vheu, vai, vv)) {
				best_move.score = -1;
				//std::cout << "\nWin(vheu)\nBestMove: " << (best_move.side == 0 ? "L" : "R");
				return best_move;
			} 
			if(win(vai, vheu, vv)) {
				best_move.score = 1;
				//std::cout << "\nWin(vai)\nBestMove: " << (best_move.side == 0 ? "L" : "R");
				return best_move;
			}
		} else if(tie(vheu, vai, vv)) {
			best_move.score = 0;
			//std::cout << "\nTie!\nBestMove: " << (best_move.side == 0 ? "L" : "R");
			return best_move;
		}

		best_move.score = maximizing_player ? -2 : 2;
		// -2 and 2 acts just like as -inf and inf
		//	Ai tries to maximize it's score and player is tring to minimize AI's score
		for(int i = 0; i <= 1; i++) {
			if((vai.size() + vheu.size()) <= vv.size() && itEndvv != itBegvv) {
				side = (i == 0) ? false : true;
				if(side) {
					vai.push_back(*itBegvv);
					itBegvv++;
				} else {
					vai.push_back(*itEndvv);
					itEndvv--;
				}
				//print();	uncomment to see AI's analizes
				Move board_state = minimax(vai, vheu, vv, itBegvv, itEndvv, !maximizing_player);
				if(maximizing_player) {
					// if we search for the worst move for player:
					if(board_state.score > best_move.score) {
						best_move.score = board_state.score;
						best_move.side = side;
					}
				} else {
					//	if the move is better than the move we'd already found or if we haven't found it yet:
					if(board_state.score < best_move.score) {
						// best move is the found one:
						best_move.score = board_state.score;
						best_move.side = side;
					}
				}
				// reset analised pole:
				if(i) {
					vai.pop_back();
					itBegvv--;
				} else {
					vai.pop_back();
					itEndvv++;
				}
			}
		}
		return best_move;
	}
}
