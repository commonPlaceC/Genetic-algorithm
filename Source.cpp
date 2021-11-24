#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <tuple>
#include <iomanip>

using chelik = std::tuple<int, int, int, int>;
using massiv_chelikov = std::vector<chelik>;

int fitness(chelik& unit) {
#define x std::get<0>(unit)
#define y std::get<1>(unit)
#define z std::get<2>(unit)
#define w std::get<3>(unit)
	if (z != w)
		//return ((x * y) + x) / (z - w);
		//return ((x + y + z) * (x * w) - y) / (z - w);
		return ((x + y + z) * (x - w) - y) / (z - w);
	else return 0;
}

void randomizer(massiv_chelikov& population) {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10000; i++) {
		population.push_back(std::make_tuple(rand() % 100, rand() % 100, rand() % 100, rand() % 100));
	}
	std::sort(population.begin(), population.end(), [](chelik unit1, chelik unit2)->bool {return fitness(unit1) > fitness(unit2); });
	while (population.size() > 300) {
		population.pop_back();
	}
}


void reproduction(massiv_chelikov& population, chelik unit1, chelik unit2) {
	srand((unsigned int)time(NULL));
	population.push_back(std::make_tuple(std::get<0>(unit2), std::get<1>(unit1), std::get<2>(unit1), std::get<3>(unit1)));
	population.push_back(std::make_tuple(std::get<0>(unit2), std::get<1>(unit2), std::get<2>(unit1), std::get<3>(unit1)));
	population.push_back(std::make_tuple(std::get<0>(unit2), std::get<1>(unit2), std::get<2>(unit2), std::get<3>(unit1)));

	population.push_back(std::make_tuple(std::get<0>(unit1), std::get<1>(unit2), std::get<2>(unit2), std::get<3>(unit2)));
	population.push_back(std::make_tuple(std::get<0>(unit1), std::get<1>(unit1), std::get<2>(unit2), std::get<3>(unit2)));
	population.push_back(std::make_tuple(std::get<0>(unit1), std::get<1>(unit1), std::get<2>(unit1), std::get<3>(unit2)));

	if (rand() % 10 == 0)
		population.push_back(std::make_tuple(rand() % 100, std::get<1>(unit2), std::get<2>(unit1), std::get<3>(unit1)));
	if (rand() % 10 == 0)
		population.push_back(std::make_tuple(rand() % 100, std::get<1>(unit2), std::get<2>(unit2), std::get<3>(unit1)));
	if (rand() % 10 == 0)
		population.push_back(std::make_tuple(rand() % 100, std::get<1>(unit1), std::get<2>(unit2), std::get<3>(unit2)));
	if (rand() % 10 == 0)
		population.push_back(std::make_tuple(rand() % 100, std::get<1>(unit1), std::get<2>(unit1), std::get<3>(unit2)));


	if (rand() % 10 == 0)
		population.push_back(std::make_tuple(std::get<0>(unit2), rand() % 100, std::get<2>(unit1), std::get<3>(unit1)));
	if (rand() % 10 == 0)
		population.push_back(std::make_tuple(std::get<0>(unit2), rand() % 100, std::get<2>(unit2), std::get<3>(unit1)));
	if (rand() % 10 == 0)
		population.push_back(std::make_tuple(std::get<0>(unit1), rand() % 100, std::get<2>(unit2), std::get<3>(unit2)));
	if (rand() % 10 == 0)
		population.push_back(std::make_tuple(std::get<0>(unit1), rand() % 100, std::get<2>(unit1), std::get<3>(unit2)));



	if (rand() % 10 == 0)
		population.push_back(std::make_tuple(std::get<0>(unit2), std::get<1>(unit1), rand() % 100, std::get<3>(unit1)));
	if (rand() % 10 == 0)
		population.push_back(std::make_tuple(std::get<0>(unit2), std::get<1>(unit2), rand() % 100, std::get<3>(unit1)));
	if (rand() % 10 == 0)
		population.push_back(std::make_tuple(std::get<0>(unit1), std::get<1>(unit2), rand() % 100, std::get<3>(unit2)));
	if (rand() % 10 == 0)
		population.push_back(std::make_tuple(std::get<0>(unit1), std::get<1>(unit1), rand() % 100, std::get<3>(unit2)));



	if (rand() % 10 == 0)
		population.push_back(std::make_tuple(std::get<0>(unit2), std::get<1>(unit2), std::get<2>(unit1), rand() % 100));
	if (rand() % 10 == 0)
		population.push_back(std::make_tuple(std::get<0>(unit2), std::get<1>(unit2), std::get<2>(unit1), rand() % 100));
	if (rand() % 10 == 0)
		population.push_back(std::make_tuple(std::get<0>(unit1), std::get<1>(unit2), std::get<2>(unit2), rand() % 100));
	if (rand() % 10 == 0)
		population.push_back(std::make_tuple(std::get<0>(unit1), std::get<1>(unit1), std::get<2>(unit2), rand() % 100));
}

void procreation(massiv_chelikov& population) {
	srand((unsigned int)time(NULL));
	size_t size_ = population.size();
	for (int i = 0; i < size_; i++) {
		reproduction(population, population[i], population[rand() % size_]);
	}
	std::sort(population.begin(), population.end(), [](chelik unit1, chelik unit2)->bool {return fitness(unit1) > fitness(unit2); });
	while (population.size() > 300) {
		population.pop_back();
	}
}

int main() {
	double sum = 0.0;
	int i = 0;
	for (; i < 50; i++) {
		massiv_chelikov population;
		randomizer(population);
		int step = 100;
		while (step) {
			procreation(population);
			step--;
		}
		sum += static_cast<int>(fitness(population[population.size() - 1]));
		std::cout << std::fixed << static_cast<int>(fitness(population[population.size() - 1])) << " " << i << std::endl;
		std::cout << std::get<0>(population[population.size() - 1]) << " " << std::get<1>(population[population.size() - 1]) << " " << std::get<2>(population[population.size() - 1]) << " " << std::get<3>(population[population.size() - 1]) << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << static_cast<double>(sum / i) << std::endl;
	return 0;
}