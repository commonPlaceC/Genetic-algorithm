#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

using person = tuple<int, int, int>;
using populations = vector<person>;


//Функция
int fitness(person &parent) {
	if (get<1>(parent) != 0) 
		// return ((get<0>(parent) - get<2>(parent)) / (2 * get<1>(parent))); // (x - z) / 2 * y
		return (get<2>(parent) - get<0>(parent) + get<0>(parent) * get<1>(parent)); // z-x + xy | z - x*(1 - y)
}


//Создание первой популяции
void createNewPopulation(populations &population_)
{
	srand((int)time(NULL));
	for (int i = 0; i < 1500; i++) {
		population_.push_back(make_tuple(rand() % 500 - 250, rand() % 500 - 250, rand() % 500 - 250));
	}
}

//Скрещивание генов
void geneCrossing(populations &population_, person parent1, person parent2) {
	srand((int)time(NULL)); 
	population_.push_back(make_tuple(get<0>(parent1), get<1>(parent2), get<2>(parent2)));
	population_.push_back(make_tuple(get<0>(parent1), get<1>(parent1), get<2>(parent2)));
	population_.push_back(make_tuple(get<0>(parent2), get<1>(parent1), get<2>(parent1)));
	population_.push_back(make_tuple(get<0>(parent2), get<1>(parent2), get<2>(parent1)));
	//Мутации
	if (rand() % 5 == 0)
		population_.push_back(make_tuple(rand() % 500 - 250, get<1>(parent1), get<2>(parent2)));
	if (rand() % 5 == 0)
		population_.push_back(make_tuple(rand() % 500 - 250, get<1>(parent2), get<2>(parent1)));
	if (rand() % 5 == 0)
		population_.push_back(make_tuple(get<0>(parent1), rand() % 500 - 250, get<2>(parent2)));
	if (rand() % 5 == 0)
		population_.push_back(make_tuple(get<0>(parent2), rand() % 500 - 250, get<2>(parent1)));
	if (rand() % 5 == 0)
		population_.push_back(make_tuple(get<0>(parent1), get<1>(parent2), rand() % 500 - 250));
	if (rand() % 5 == 0)
		population_.push_back(make_tuple(get<0>(parent2), get<1>(parent1), rand() % 500 - 250));

}

//Размножение
void reproduction(populations &population_) {

	srand((int)time(NULL));
	size_t size_ = population_.size();

	for (int i = 0; i < size_; i++) {
		geneCrossing(population_, population_[rand() % population_.size()], population_[rand() % population_.size()]);
	}

	sort(population_.begin(), population_.end(), [](person parent1, person parent2) { return fitness(parent1) > fitness(parent2); });

	while (population_.size() > 1500) {
		population_.pop_back();
	}
}


//Главная функция
int main() {

	auto start = high_resolution_clock::now();

	populations population_;
	createNewPopulation(population_);

	int try_ = 100;
	while (try_) {
		reproduction(population_);
		try_--;
	}
	cout << "Final result of algorithm: " << fitness(population_[population_.size() - 1]) << endl;
	cout << "With values: " << get<0>(population_[population_.size() - 1]) << " " << get<1>(population_[population_.size() - 1]) << " " << get<2>(population_[population_.size() - 1]) << endl;

	auto stop = high_resolution_clock::now();
	auto time = duration_cast<microseconds>(stop - start);
	cout << time.count() / 1000000.0 << " - seconds taken";


	return 0;
}