#include "Game.hpp"
#include "Ai.hpp"

namespace mro {
	Game::Game(size_t stone_amount, int min_val, int max_val) : size{stone_amount}, min{min_val}, max{max_val} {
		vv = make_random_vector(size, min, max);
		vleft = vv;
		itBegvv = vv.begin();
		itEndvv = vv.end() - 1;
		Ai ai;
		this->Run();
	}

	std::vector<int> Game::make_random_vector(size_t size, int min_value, int max_value) {
		//static_assert(std::is_arithmetic_v< int >, "int must be an arithmetic type");

		std::mt19937 prng{std::random_device{}()};
		std::vector<int> ret_v;
		ret_v.reserve(size);
		auto bi = std::back_inserter(ret_v);

		using dist_t = std::conditional_t<std::is_integral_v<int>,
			 std::uniform_int_distribution<int>,
			 std::uniform_real_distribution<int>>;

		dist_t dist{min_value, max_value};
		std::generate_n(bi, size, [&]() { return dist(prng); });

		return ret_v;
	}

	void Game::print(std::vector<int> wektor) {
		int licz = 0;
		for(const int i : wektor) {
			licz++;
			std::cout << i << (licz % 10 == 0 ? "\n" : " ");
		}
		std::cout << std::endl;
	}

	void Game::player_move(std::vector<int>& vai, std::vector<int>& vheu, std::vector<int>& vv, std::vector<int>& vleft, std::vector<int>::iterator& itBegvv, std::vector<int>::iterator& itEndvv) {
		while(true) {
			char imput;
			try {
				if(*itEndvv != *itBegvv) {
					std::cout << "\nEnter a number you want to take (" << *itBegvv << " or " << *itEndvv << "): ";
					std::cin >> imput;
					int cell = imput - '0';
					bool a = bool(cell == *itBegvv);
					bool b = bool(cell == *itEndvv);
					// cin.fail() --> fail if type is not correct
					if(std::cin.fail() || (static_cast<int>(cell) != cell) || !(a || b)) {
						std::cout << "\nWrong input. Please enter one integer\n";
						std::cin.clear();
						std::cin.ignore(256, '\n'); // ignore the line change
						player_move(vai, vheu, vv, vleft, itBegvv, itEndvv);
					}
					bool left_number;
					left_number = a ? true : false;

					if((vai.size() + vheu.size()) != vv.size()) {
						if(left_number) {
							vheu.push_back(*itBegvv);
							itBegvv++;
							if(vleft.size() > 0)
								vleft.erase(vleft.begin());
						} else {
							vheu.push_back(*itEndvv);
							itEndvv--;
							vleft.pop_back();
						}
						break;
					}
				} else {
					std::cout << "\nEnter L or R";
					std::cin >> imput;
					// cin.fail() --> fail if type is not correct
					if(std::cin.fail() || (imput != 'L' && imput != 'R' && imput != 'l' && imput != 'r')) {
						std::cout << "\nWrong input. Please enter one integer\n";
						std::cin.clear();
						std::cin.ignore(256, '\n'); // ignore the line change
						player_move(vai, vheu, vv, vleft, itBegvv, itEndvv);
					}
					bool left_number;
					left_number = (imput == 'L') ? true : false;

					if((vai.size() + vheu.size()) != vv.size()) {
						if(left_number) {
							vheu.push_back(*itBegvv);
							itBegvv++;
							if(vleft.size() > 0)
								vleft.erase(vleft.begin());
						} else {
							vheu.push_back(*itEndvv);
							itEndvv--;
							vleft.pop_back();
						}
						break;
					}
				}
			} catch(std::exception& e) {
				std::cout << "\nYou entered: " << e.what() << "\nAnd you were ment to enter the first or the last number of vector\n";
			}
		}
	}

	void Game::computer_move(std::vector<int>& vai, std::vector<int>& vheu, std::vector<int>& vv, std::vector<int>& vleft, std::vector<int>::iterator& itBegvv, std::vector<int>::iterator& itEndvv) {
		Move best_move = ai.minimax(vai, vheu, vv, itBegvv, itEndvv);
		if(best_move.side) {
			vai.push_back(*itBegvv);
			if(vleft.size() > 0)
				vleft.erase(vleft.begin());
			itBegvv++;
		} else {
			vai.push_back(*itEndvv);
			vleft.pop_back();
			itEndvv--;
		}
	}

	void Game::Run() {
		int player, computer;
		char imput{};

		while(true) {
			std::cout << "Wanna begin (y or n)? ";
			std::cin >> imput;
			if(imput == 'y' || imput == 'n' || imput == 'Y' || imput == 'N') {
				break;
			}
		}
		if(imput == 'y' || imput == 'Y')
			player = 1;
		if(imput == 'n' || imput == 'N')
			player = 2;
		computer = player == 1 ? 2 : 1;

		if(player == 2) {
			std::cout << "Last stones: ";
			print(vleft);
			std::cout << "\nComputer is making a move...";
			computer_move(vai, vheu, vv, vleft, itBegvv, itEndvv);
			std::cout << "\nComputer stones: ";
			print(vai);
		}

		// main game loop:
		while(true) {
			std::cout << "Last stones: ";
			print(vleft);
			player_move(vai, vheu, vv, vleft, itBegvv, itEndvv);
			std::cout << "Player stones: ";
			print(vheu);

			if(ai.win(vheu, vai, vv)) {
				std::cout << "\nPlayer wins!\nScore: " << std::accumulate(vheu.begin(), vheu.end(), 0) << "\nvheu: ";
				print(vheu);
				std::cout << "\nComputer looses!\nScore: " << std::accumulate(vai.begin(), vai.end(), 0) << "\n vai: ";
				print(vai);
				return;
			} else if(ai.tie(vheu, vai, vv)) {
				std::cout << "\nTie!";
				std::cout << "\nComputer score: " << std::accumulate(vai.begin(), vai.end(), 0) << "\n vai: ";
				print(vai);
				std::cout << "\nPlayer score: " << std::accumulate(vheu.begin(), vheu.end(), 0) << "\nvheu: ";
				print(vheu);
				return;
			}

			std::cout << "Computer is making a move...";
			computer_move(vai, vheu, vv, vleft, itBegvv, itEndvv);
			std::cout << "\nComputer stones: ";
			print(vai);

			if(ai.win(vai, vheu, vv)) {
				std::cout << "\nComputer wins!\nScore: " << std::accumulate(vai.begin(), vai.end(), 0) << "\n vai: ";
				print(vai);
				std::cout << "\nPlayer looses!\nScore: " << std::accumulate(vheu.begin(), vheu.end(), 0) << "\nvheu: ";
				print(vheu);
				return;
			} else if(ai.tie(vai, vheu, vv)) {
				std::cout << "\nTie!";
				std::cout << "\nComputer score: " << std::accumulate(vai.begin(), vai.end(), 0) << "\n vai: ";
				print(vai);
				std::cout << "\nPlayer score: " << std::accumulate(vheu.begin(), vheu.end(), 0) << "\nvheu: ";
				print(vheu);
				return;
			}
		}
	}
}
