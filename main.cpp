#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

using person = tuple<int, int, int>;
using populations = vector<person>;


//Функция
int fitness(person &unit) {
	if (get<1>(unit) != 0) 
		return ((get<0>(unit) - get<2>(unit)) / (2 * get<1>(unit))); // (x - z) / 2 * y
}


//Создание первой популяции
void createNewPopulation(populations &population_)
{
	srand((int)time(NULL));
	for (int i = 0; i < 1000; i++) {
		population_.push_back(make_tuple(rand() % 500, rand() % 500, rand() % 500));
	}
}

//Скрещивание генов
void geneCrossing(populations &population_, person unit1, person unit2) {
	srand((int)time(NULL)); 
	population_.push_back(make_tuple(get<0>(unit1), get<1>(unit2), get<2>(unit2)));
	population_.push_back(make_tuple(get<0>(unit1), get<1>(unit1), get<2>(unit2)));
	population_.push_back(make_tuple(get<0>(unit2), get<1>(unit1), get<2>(unit1)));
	population_.push_back(make_tuple(get<0>(unit2), get<1>(unit2), get<2>(unit1)));
	//--
	population_.push_back(make_tuple(rand() % 500, get<1>(unit1), get<2>(unit2)));
	population_.push_back(make_tuple(rand() % 500, get<1>(unit2), get<2>(unit1)));
	//--
	population_.push_back(make_tuple(get<0>(unit1), rand() % 500, get<2>(unit2)));
	population_.push_back(make_tuple(get<0>(unit2), rand() % 500, get<2>(unit1)));
	//--
	population_.push_back(make_tuple(get<0>(unit1), get<1>(unit2), rand() % 500));
	population_.push_back(make_tuple(get<0>(unit2), get<1>(unit1), rand() % 500));

}

//Размножение
void reproduction(populations &population_) {
	srand((int)time(NULL));
	size_t size_ = population_.size();
	for (int i = 0; i < size_; i++) {
		geneCrossing(population_, population_[rand() % population_.size()], population_[rand() % population_.size()]);
	}
	sort(population_.begin(), population_.end(), [](person unit1, person unit2) { return fitness(unit1) > fitness(unit2); });

	while (population_.size() > 1000){
		population_.pop_back();
	}
}


//Главная функция
int main() {
	populations population_;
	createNewPopulation(population_);

	int try_ = 100;
	while (try_) {
		reproduction(population_);
		try_--;
	}
	cout << fitness(population_[population_.size() - 1]) << endl;
	cout << endl;
	cout << get<0>(population_[population_.size() - 1]) << " " << get<1>(population_[population_.size() - 1]) << " " << get<2>(population_[population_.size() - 1]);
	return 0;
}