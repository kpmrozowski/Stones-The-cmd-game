#include <iostream>

#include "Ai.hpp"

namespace mro {
	Ai::Ai() {}

	bool Ai::win(std::vector<int>& win, std::vector<int>& lose, std::vector<int>& vv) {
		bool a = ((win.size() + lose.size()) != vv.size());
		bool b = (win.size() != lose.size());
		bool c = (std::accumulate(win.begin(), win.end(), 0) >= std::accumulate(lose.begin(), lose.end(), 0));
		bool iswin = true;
		if(a || b || c)
			iswin = false;
		if(iswin)
			return true;
		return false;
	}

	bool Ai::tie(std::vector<int>& vai, std::vector<int>& vheu, std::vector<int>& vv) {
		if(win(vai, vheu, vv))
			return false;
		bool a = (vai.size() + vheu.size()) == vv.size();
		bool b = vai.size() == vheu.size();
		bool c = std::accumulate(vai.begin(), vai.end(), 0) == std::accumulate(vheu.begin(), vheu.end(), 0);
		if(a && b && c)
			return true;
		return false;
	}

	void Ai::computer_move(std::vector<int>& vai, std::vector<int>& vheu, std::vector<int>& vv, std::vector<int>& vleft, std::vector<int>::iterator& itBegvv, std::vector<int>::iterator& itEndvv, bool maximizing_player) {
		//bestMovesVect = std::vector<Move>(2, Move(0));
		//for(Move& move : movesVect) {
		//	move.score = 0;
		//	move.win = 0;
		//	move.lose = 0;
		//	move.tie = 0;
		//	move.side = 0;
		//}
		//for(Move& move : bestMovesVect) {
		//	move.score = 0;
		//	move.win = 0;
		//	move.lose = 0;
		//	move.tie = 0;
		//	move.side = 0;
		//}
		Move best_move = minimax(vai, vheu, vv, itBegvv, itEndvv, maximizing_player);
		if(best_move.side == 'L' && vleft.size() > 0) {
			vai.push_back(*itBegvv);
			vleft.erase(vleft.begin());
			itBegvv++;
		}
		if(best_move.side == 'R' && vleft.size() > 0) {
			itEndvv--;
			vai.push_back(*itEndvv);
			vleft.pop_back();
		}
		std::cout << " " << (best_move.side == 'L' ? "L" : "R");
		int licz = 1;
		//for(Move move : movesVect) {
		//	bestMovesVect[move.side == 'L' ? 0 : 1].score += move.score;
		//	bestMovesVect[move.side == 'L' ? 0 : 1].win += move.win;
		//	bestMovesVect[move.side == 'L' ? 0 : 1].lose += move.lose;
		//	bestMovesVect[move.side == 'L' ? 0 : 1].tie += move.tie;
		//	bestMovesVect[move.side == 'L' ? 0 : 1].side = move.side;
		//	//std::cout << "\n" << licz << ".\tside = " << (move.side == 'L' ? "L" : "R") << "   score = " << move.score;
		//}

		//std::cout << "\nBest moves (sorted best to worst):";
		//for(Move move : bestMovesVect) {
		//	std::cout << "\n|" << (move.side == 'L' ? "L" : "R") << "|. "
		//				 << "  wins=" << move.win << "  tie=" << move.tie << "  lose=" << move.lose << "   score=" << move.score;
		//}
	}

	Move Ai::minimax(std::vector<int>& vai, std::vector<int>& vheu, std::vector<int>& vv, std::vector<int>::iterator& itBegvv, std::vector<int>::iterator& itEndvv, bool maximizing_player) {
		Move best_move;
		// If maximizing_player wins we can return -1
		//		and if maximizing_player loses we
		//		returns 1;
		if(maximizing_player) {
			if(win(vheu, vai, vv)) {
				best_move.score = -1;
				return best_move;
			} else if(win(vai, vheu, vv)) {
				best_move.score = 1;
				return best_move;
			} else if(tie(vheu, vai, vv)) {
				best_move.score = 0;
				//std::cout << "\nTie!\nBestMove: " << (best_move.side == 0 ? "L" : "R");
				return best_move;
			}
		} 
		if(!maximizing_player){
			if(win(vheu, vai, vv)) {
				best_move.score = -1;
				return best_move;
			} else if(win(vai, vheu, vv)) {
				best_move.score = 1;
				return best_move;
			} else if(tie(vheu, vai, vv)) {
				best_move.score = 0;
				//std::cout << "\nTie!\nBestMove: " << (best_move.side == 0 ? "L" : "R");
				return best_move;
			}
		}

		best_move.score = maximizing_player ? -2 : 2;
		// -2 and 2 acts just like as -inf and inf
		//	Ai tries to maximize it's score and player is tring to minimize AI's score
		for(int i = 0; i <= 1; i++) {
			//if(vai.size() + vheu.size() != vv.size()) {
			if(itEndvv != itBegvv) {
				char side = (i == 0) ? 'L' : 'R';
				//std::cout << side;
				if(maximizing_player) {
					if(side == 'L') {
						vai.push_back(*itBegvv);
						itBegvv++;
					}
					if(side == 'R') {
						itEndvv--;
						vai.push_back(*itEndvv);
					}
				} else {
					if(side == 'L') {
						vheu.push_back(*itBegvv);
						itBegvv++;
					}
					if(side == 'R') {
						itEndvv--;
						vheu.push_back(*itEndvv);
					}
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
				if(maximizing_player) {
					if(side == 'L' && vai.size() > 0) {
						vai.pop_back();
						itBegvv--;
					}
					if(side == 'R' && vai.size() > 0) {
						vai.pop_back();
						itEndvv++;
					}
				} else {
					if(side == 'L' && vheu.size() > 0) {
						vheu.pop_back();
						itBegvv--;
					}
					if(side == 'R' && vheu.size() > 0) {
						vheu.pop_back();
						itEndvv++;
					}
				}
			}
		}
		//best_move.win = best_move.score == 1 ? 1 : 0;
		//best_move.lose = best_move.score == -1 ? 1 : 0;
		//best_move.tie = best_move.score == 0 ? 1 : 0;
		//movesVect.push_back(best_move);
		//std::cout << (best_move.side == 'L' ? "L" : "R");
		return best_move;
	}
}
