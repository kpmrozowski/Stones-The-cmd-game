#pragma once

#include <memory>
#include <iostream>
#include <vector>
#include <string>

#include "Ai.hpp"

namespace mro {
	class Game {
		public:
		Game(size_t stone_amount, int min_val, int max_val);
		~Game(){};

		std::vector< int > make_random_vector(size_t size, int min_value, int max_value);
		void print(std::vector< int > wektor);
		void player_move(std::vector<int>& vai, std::vector<int>& vheu, std::vector<int>& vv, std::vector<int>& vleft, std::vector<int>::iterator& itBegvv, std::vector<int>::iterator& itEndvv);

		bool maximizing_player;
		std::vector<int> vv;
		std::vector<int> vleft;
		std::vector<int> vai{};
		std::vector<int> vheu{};
		std::vector<int>::iterator itBegvv;
		std::vector<int>::iterator itEndvv;

		private:
		size_t size;
		int min, max;
		Ai ai;

		void Run(); // will be called to start a game
	};
}