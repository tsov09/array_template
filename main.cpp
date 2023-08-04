
#include <iostream>
#include <stdlib.h>
#include <time.h>


template <class T>
class Array {
public:
	Array() {
		this->size = 10;
		this->ptr = new T[this->size];
		this->fill_array();
	}
	Array(int size) {
		this->size = size;
		this->ptr = new T[this->size];
		this->fill_array();
	}
	~Array() {
		delete[] this->ptr;
	}
	Array(const Array<T>& obj) {
		this->size = obj.size;
		this->ptr = new T[this->size];
		for (int i = 0; i < this->size; i++) {
			this->ptr[i] = obj.ptr[i];
		}
	}
	Array(Array<T>&& obj) {
		std::cout << "Array move con-tor" << std::endl;
		this->size = obj.size;
		this->ptr = obj.ptr;
		obj.ptr = nullptr;
		obj.size = 0;
	}
	Array<T>& operator = (const Array<T>& obj) {
		if (this != &obj) {
			delete[] this->ptr;
			this->ptr = nullptr;
			this->size = obj.size;
			this->ptr = new T[this->size];
			for (int i = 0; i < this->size; i++) {
				this->ptr[i] = obj.ptr[i];
			}
		}
		return *this;
	}
	Array<T>& operator = (Array<T>&& obj) {
		std::cout << "Array op. move assign." << std::endl;
		if (this != &obj) {
			delete[] this->ptr;
			this->ptr = nullptr;
			this->size = obj.size;
			this->ptr = obj.ptr;
			obj.ptr = nullptr;
			obj.size = 0;
		}
		return *this;
	}
	T& operator[] (int i) {
		if (i >= this->size || i < 0) {
			std::cout << "The number is out of range" << std::endl << std::endl;
			exit(0);
		}
		else {
			return this->ptr[i];
		}
	}
private:
	T* ptr;
	int size;
	void fill_array() {
		for (int i = 0; i < this->size; i++) {
			this->ptr[i] = rand() % 100 + 10;
		}
	}
public:
	T gen_element(int x) {
		if (x >= this->size || x < 0) {
			std::cout << "The number is out of range" << std::endl << std::endl;
			exit(0);
		}
		else {
			return this->ptr[x];
		}
	}
	void push_back(T item) {
		this->size++;
		T* temp_ptr = this->ptr;
		this->ptr = new T[this->size];
		for (int i = 0; i < this->size - 1; i++) {
			this->ptr[i] = temp_ptr[i];
		}
		this->ptr[this->size - 1] = item;
		delete[] temp_ptr;
		temp_ptr = nullptr;
	}
	void pop_back() {
		this->size--;
		T* temp_ptr = this->ptr;
		this->ptr = new T[this->size];
		for (int i = 0; i < this->size; i++) {
			this->ptr[i] = temp_ptr[i];
		}
		//this->ptr[this->size - 1] = item;
		delete[] temp_ptr;
		temp_ptr = nullptr;
	}
	int length() {
		return this->size;
	}
	void print() {
		std::cout << "{ ";
		for (int i = 0; i < this->size - 1; i++) {
			std::cout << this->ptr[i] << ", ";
		}
		std::cout << this->ptr[this->size - 1] << " }";

	}
};

template <typename T>
class Stack : private Array<T> {
public:
	void push(T item) {
		this->push_back(item);
	}
	void pop() {
		this->pop_back();
	}
	T top() {
		return this->gen_element(this->length() - 1);
	}
};

void check_array() {
	std::cout << std::endl;

	Array<int> arr_i;
	std::cout << "Array of 10 elements: " << std::endl;
	arr_i.print();

	std::cout << std::endl;
	arr_i.push_back(1000);
	std::cout << "Array after call push_back(...): " << std::endl;
	arr_i.print();
	std::cout << std::endl;
	arr_i.pop_back();
	std::cout << "Array after call pop_back(): " << std::endl;
	arr_i.print();
	std::cout << std::endl;

	//Array<double> arr_d;
	//arr_d.print();
}
int main() {
	srand(time(NULL));

	Stack<int>* stack = new Stack<int>();
	std::cout << "Stack:" << std::endl;
	stack->push(56);
	std::cout << "Top after push(...) 56: " << stack->top() << std::endl;
	stack->push(75);
	std::cout << "Top after push(...) 75: " << stack->top() << std::endl;
	stack->push(23);
	std::cout << "Top after push(...) 23: " << stack->top() << std::endl;
	stack->pop();
	std::cout << "Top after single pop(): " << stack->top() << std::endl;


	delete stack;
	return 0;
}
