#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <limits.h>
#include <chrono>

//Определение переменых
#define x get<0>(parent)
#define y get<1>(parent)
#define z get<2>(parent)

using namespace std;
using namespace std::chrono; //Подсчет времени

using person = tuple<int, int, int>;
using populations = vector<person>;


//Ввод и проверка ввода
int userInput() {
    int num;
    while(!((cin >> num) && (num == 1 || num == 2))) {
        cin.clear();
        cin.ignore(32276,'\n');
        cout << "Wrong value! Please enter again:  ";
    };
    return num;
}

//Функция
int fitness(const person &parent, const __int16 &funcNum) {
	if (y != 0 && funcNum == 1) 
		return (x - z) / (2 * y); // (x - z) / 2 * y  maximum: 250
	else if (funcNum == 2)
		return (z - x + x * y); // z-x + xy | z - x*(1 - y)  maximum: 63000
	else
		return INT_MIN;
}


//Создание первой популяции
void createNewPopulation(populations &population_) {
	srand((int)time(NULL));
	for (int i = 0; i < 1500; i++) {
		population_.push_back(make_tuple(rand() % 501 - 250, rand() % 501 - 250, rand() % 501 - 250));
	}
}

//Кроссинговер
void geneCrossing(populations &population_, person parent1, person parent2) {
	srand((int)time(NULL)); 
	population_.push_back(make_tuple(get<0>(parent1), get<1>(parent2), get<2>(parent2)));
	population_.push_back(make_tuple(get<0>(parent1), get<1>(parent1), get<2>(parent2)));
	population_.push_back(make_tuple(get<0>(parent2), get<1>(parent1), get<2>(parent1)));
	population_.push_back(make_tuple(get<0>(parent2), get<1>(parent2), get<2>(parent1)));
	//Мутации c вероятностью 25%)
	{
	if (rand() % 4 == 0)
		population_.push_back(make_tuple(rand() % 501 - 250, get<1>(parent1), get<2>(parent2)));
	if (rand() % 4 == 0)
		population_.push_back(make_tuple(rand() % 501 - 250, get<1>(parent2), get<2>(parent1)));
	if (rand() % 4 == 0)
		population_.push_back(make_tuple(get<0>(parent1), rand() % 501 - 250, get<2>(parent2)));
	if (rand() % 4 == 0)
		population_.push_back(make_tuple(get<0>(parent2), rand() % 501 - 250, get<2>(parent1)));
	if (rand() % 4 == 0)
		population_.push_back(make_tuple(get<0>(parent1), get<1>(parent2), rand() % 501 - 250));
	if (rand() % 4 == 0)
		population_.push_back(make_tuple(get<0>(parent2), get<1>(parent1), rand() % 501 - 250));
	}

}

//Селекция
void selection(populations &population_, const __int16 &funcNum) {
	sort(population_.begin(), population_.end(), [&](person parent1, person parent2) { return fitness(parent1, funcNum) > fitness(parent2, funcNum); });

	while (population_.size() > 1500) {
		population_.pop_back();
	}
}

//Размножение
void reproduction(populations &population_, const __int16 &funcNum) {

	srand((int)time(NULL));
	size_t size_ = population_.size();

	for (int i = 0; i < size_; i++) {
		geneCrossing(population_, population_[rand() % population_.size()], population_[rand() % population_.size()]);
	}

	selection(population_, funcNum);
}


//Главная функция
int main() {

	cout << "Please enter the number of function: (1/2): "; //Выбор функции
	__int16 funcNum = userInput();
	system("CLS");

	auto start = high_resolution_clock::now();

	populations population_; 
	createNewPopulation(population_);

	__int16 try_ = 150; //Запуск алгоритма
	while (try_) {
		reproduction(population_, funcNum);
		try_--;
	}
	auto stop = high_resolution_clock::now();
	auto time = duration_cast<milliseconds>(stop - start);

	double result = fitness(population_[0], funcNum); //Вывод результатов
	cout << "\tFinal result of algorithm: " << result << endl;
	cout << "\tWith values: x = " << get<0>(population_[0]);
	cout << "; y = " << get<1>(population_[0]);
	cout << "; z = " << get<2>(population_[0]) << "\n\n";
	cout << "\t\tStats:\n";
	cout << time.count() / 1000.0 << " - seconds taken\t";
	if (funcNum == 1)
		cout <<"Accuracy - " << result / 250.0 * 100 << "%\n";
	else 
		cout <<"Accuracy - " << result / 63000.0 * 100 << "%\n";

	return 0;
}