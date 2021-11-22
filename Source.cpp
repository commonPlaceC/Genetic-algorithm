#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <tuple>

using chelik = std::tuple<int, int, int, int>;
using massiv_chelikov = std::vector<chelik>;

double fitness(chelik& unit) {
	if (std::get<2>(unit) != std::get<3>(unit))
		return ((std::get<0>(unit) * std::get<1>(unit)) + std::get<0>(unit)) / ((std::get<2>(unit) - std::get<3>(unit)));
	//((x*y)+x)/(z-w)
}

void randomizer(massiv_chelikov& population) {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 300; i++) {
		population.push_back(std::make_tuple(rand() % 100, rand() % 100, rand() % 100, rand() % 100));
	}
}


void reproduction(massiv_chelikov& population, chelik unit1, chelik unit2) {
	population.push_back(std::make_tuple(std::get<0>(unit2), std::get<1>(unit1), std::get<2>(unit1), std::get<3>(unit1)));
	population.push_back(std::make_tuple(std::get<0>(unit2), std::get<1>(unit2), std::get<2>(unit1), std::get<3>(unit1)));
	population.push_back(std::make_tuple(std::get<0>(unit2), std::get<1>(unit2), std::get<2>(unit2), std::get<3>(unit1)));
	population.push_back(std::make_tuple(std::get<0>(unit1), std::get<1>(unit2), std::get<2>(unit2), std::get<3>(unit2)));
	population.push_back(std::make_tuple(std::get<0>(unit1), std::get<1>(unit1), std::get<2>(unit2), std::get<3>(unit2)));
	population.push_back(std::make_tuple(std::get<0>(unit1), std::get<1>(unit1), std::get<2>(unit1), std::get<3>(unit2)));
}

void procreation(massiv_chelikov& population) {
	srand((unsigned int)time(NULL));
	size_t size_ = population.size();
	for (int i = 0; i < size_; i++) {
		reproduction(population, population[rand() % population.size()], population[rand() % population.size()]);
	}
	std::sort(population.begin(), population.end(), [](chelik unit1, chelik unit2)->bool {return fitness(unit1) > fitness(unit2); });
	while (population.size() > 300) {
		population.pop_back();
	}
}	

int main() {
	massiv_chelikov population;
	randomizer(population);

	int step = 100;
	while (step) {
		procreation(population);
		step--;
	}
		std::cout << fitness(population[population.size()-1]) << std::endl;

	std::cout << std::endl;

	std::cout << std::get<0>(population[population.size() - 1]) << " " << std::get<1>(population[population.size() - 1]) << " " << std::get<2>(population[population.size() - 1]) << " " << std::get<3>(population[population.size() - 1]) << std::endl;


	return 0;
}
