#include <iostream>
#include <ctime>
using namespace std;

struct Print; //предварительное описание класса-стратегии
// Класс-контекст
class ArrayContext {

private:
	Print* strategy_;
	int lenght_;
	int* arr;

public:
	//конструктор по умолчанию
	ArrayContext() {
		strategy_ = nullptr;
		lenght_ = 0;
		arr = nullptr;
	}
	//конструктор с одним параметром
	ArrayContext(int length) {
		if (length < 0) {
			throw std::invalid_argument("Array length is a negative number");
		}
		else {
			lenght_ = length;
			arr = new int[lenght_];
		}
	}
	//конструктор с двумя параметрами
	ArrayContext(int length, Print* strategy) {
		if (length < 0) {
			throw std::invalid_argument("Array length is a negative number");
		}
		else {
			lenght_ = length;
			arr = new int[length];
			strategy_ = strategy;
		}

	}

	void fillArray() {
		/*
		srand(time(NULL));
		for (int i = 0; i < lenght_; i++) {
			arr[i]= rand();
		}
		*/
		for (int i = 0; i < lenght_; i++) {
			arr[i] = i;
		}
	}

	int getSize() { return lenght_; }

	Print* getStrategy() {
		return strategy_;
	}
	int* getArray() { return arr; }


	//перегрузка оператора индексирования элементов массива
	int& operator[](int i) {
		return arr[i];
	}
	void setStrategy(Print* strategy) {
		strategy_ = strategy;
	}
	~ArrayContext() {
		delete[] arr;
		delete strategy_;
	}

	void useStrategy();
};
//  Базовая стратегия

struct Print {
	virtual void print(int* array, int lenght) = 0;
};

// Конкретные стратегии

//печать по одному элементу в строке
struct PrintOneByOne : Print {
	virtual void print(int* array, int lenght) {
		for (int i = 0; i < lenght; i++) {
			cout << array[i] << endl;
		}

	}
};

//печать по n элементов в строке через пробел
struct PrintNInLine : Print {
	int n_;
	PrintNInLine(int n) : n_(n) {}
	virtual void print(int* array, int lenght) {

		if (n_ > lenght) {
			throw std::invalid_argument("The number of array elements in a line when printing cannot be greater than the length of characters");
		}
		else {
			for (int i = 0; i < lenght; i++) {
				cout << array[i] << " ";
				if ((i + 1) % n_ == 0) {
					cout << endl;
				}
			}
			cout << endl;
		}

	}


};
void ArrayContext::useStrategy() {
	strategy_->print(arr, lenght_);
}


int main()
{
	Print * s1 = new PrintOneByOne(); // создаем две разные стратегии
	Print* s2 = new PrintNInLine(2);

	ArrayContext * arr = new ArrayContext(10);
	arr->fillArray();

	arr->setStrategy(s2);
	arr->useStrategy();

	//меняем стратегию
	arr->setStrategy(s1);
	arr->useStrategy();
}
