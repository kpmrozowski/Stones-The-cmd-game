#pragma once

#include <random>
#include <type_traits>
#include <typeinfo>
#include <algorithm>
#include <numeric>

namespace mro{
	struct Move {
		bool side;
		int score;
	};

	class Ai {
		public:
		Ai(){};
		Ai(std::vector<int>& vv, std::vector<int>::iterator& itBegvv, std::vector<int>::iterator& itEndvv);
		~Ai(){};

		Move minimax(std::vector<int>& vai, std::vector<int>& vheu, std::vector<int>& vv, bool maximizing_heu, std::vector<int>::iterator& itBegvv, std::vector<int>::iterator& itEndvv);

		bool win(std::vector<int>& win, std::vector<int>& lose, std::vector<int>& vv);
		bool tie(std::vector<int>& win, std::vector<int>& lose, std::vector<int>& vv);
	};
}