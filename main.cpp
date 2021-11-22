#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

using chelik = tuple<int, int, int, int>;
using massiv_chelikov = vector<chelik>;


double func(chelik& unit) {
	if (get<2>(unit) != get<3>(unit))
		return ((get<0>(unit) * get<1>(unit)) + get<0>(unit)) / ((get<2>(unit) - get<3>(unit)));
}


//Создание первой популяции
void randomizer(massiv_chelikov& population) {
	srand((int)time(NULL));
	for (int i = 0; i < 100; i++) {
		population.push_back(make_tuple(rand() % 100, rand() % 100, rand() % 100, rand() % 100));
	}
}

//Скрещивание 
void reproduction(massiv_chelikov& population, chelik unit1, chelik unit2) {

	population.push_back(make_tuple(get<0>(unit2), get<1>(unit1), get<2>(unit1), get<3>(unit1)));
	population.push_back(make_tuple(get<0>(unit2), get<1>(unit2), get<2>(unit1), get<3>(unit1)));
	population.push_back(make_tuple(get<0>(unit2), get<1>(unit2), get<2>(unit2), get<3>(unit1)));

    population.push_back(make_tuple(get<0>(unit1), get<1>(unit2), get<2>(unit2), get<3>(unit2)));
	population.push_back(make_tuple(get<0>(unit1), get<1>(unit1), get<2>(unit2), get<3>(unit2)));
	population.push_back(make_tuple(get<0>(unit1), get<1>(unit1), get<2>(unit1), get<3>(unit2)));
}


//Функция размножения 
void procreation(massiv_chelikov& population) {
	srand((int)time(NULL));
	size_t size_ = population.size();
	for (int i = 0; i < size_; i++) {
		reproduction(population, population[rand() % population.size()], population[rand() % population.size()]);
	}
	sort(population.begin(), population.end(), [](chelik unit1, chelik unit2) {return func(unit1) < func(unit2); });
	while (population.size() > 100) {
		population.erase(population.begin());
	}
}



int main() {
	massiv_chelikov population;
	randomizer(population);

	int step = 1000;
	while (step) {
		procreation(population);
		step--;
	}
	int count = 0;
	for (int i = 0; i < population.size(); i++) {
		cout << func(population[i]) << endl;
		count++;
	}
	cout << endl;
	cout << get<0>(population[population.size() - 1]) << " " << get<1>(population[population.size() - 1]) << " " << get<2>(population[population.size() - 1]) << " " << get<3>(population[population.size() - 1]) << endl;
	return 0;
}