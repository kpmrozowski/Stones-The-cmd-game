#pragma once

#include <random>
#include <type_traits>
#include <typeinfo>
#include <algorithm>
#include <numeric>

namespace mro{
	struct Move {
		Move() {}
		Move(int s) : score{s}, win{s}, lose{s}, tie{s} {}
		char side;
		int score{}, win{}, lose{}, tie{};
	};

	class Ai {
		public:
		Ai();
		~Ai(){};

		void computer_move(std::vector<int>& vai, std::vector<int>& vheu, std::vector<int>& vv, std::vector<int>& vleft, std::vector<int>::iterator& itBegvv, std::vector<int>::iterator& itEndvv, bool maximizing_player);
		Move minimax(std::vector<int>& vai, std::vector<int>& vheu, std::vector<int>& vv, std::vector<int>::iterator& itBegvv, std::vector<int>::iterator& itEndvv, bool maximizing_player);

		bool win(std::vector<int>& win, std::vector<int>& lose, std::vector<int>& vv);
		bool tie(std::vector<int>& win, std::vector<int>& lose, std::vector<int>& vv);

		std::vector<Move> movesVect{};
		std::vector<Move> bestMovesVect{};
	};
}