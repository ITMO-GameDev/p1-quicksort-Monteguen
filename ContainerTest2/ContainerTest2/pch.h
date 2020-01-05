//
// pch.h
// Header for standard system include files.
//

#pragma once

#include "gtest/gtest.h"
template < typename T>
class Array final {
private:
	int size_memory;
	T *A;
	int _size;

public:
	class Iterator {
		T *B = new T;
		Array<T> *fg;
	public:
		/*Iterator(T *f) {
			B = f;
			Bfirst = f;
		};*/

		Iterator(Array<T> *f) {
			fg = f;
			B = fg->A;
		};
		T& get() {
			return *B;
		};
		void set(const T& value) {
			*B = value;
		};
		bool hasNext() {
			return ((B + 1 - fg->A) <= fg->_size);
		};
		void next() {
			if (hasNext()) B = B + 1;
		};
		bool hasPrev() {
			return (B != fg->A);
		};
		void prev() {
			if (hasPrev()) B = B - 1;
		};
		void insert(const T& value) {

			for (T* K = &fg->A[fg->_size]; K > B; K--) {
				*(K) = std::move(*(K-1));
			};
			*B = value;
			fg->_size++;
		}
		void remove() {
			for (T* K = B; K < B + fg->_size-1; K++) {
				*K = std::move(*(K + 1));
			};
			fg->_size--;
		};
		void toIndex(int index) {
			B = fg->A + index;
		};
	};

	Array() {
		size_memory = 8;
		_size = 0;
		A = new T[size_memory];
		//for (int i = 0; i < size_memory; i++) A[i] = NULL;
	};
	Array(int capacity) {
		size_memory = capacity;
		_size =0;
		A = new T[size_memory];
		//for (int i = 0; i < size_memory; i++) A[i] = NULL;
	};
	Array(Array& r) {
		size_memory = r.size_memory;
		delete[]A;
		A = new T[size_memory];
		for (int i = 0; i < size_memory; i++) A[i] = r[i];
	};
	Array& operator = (Array &r) {
		size_memory = r.size_memory;
		delete[]A;
		A = new T[size_memory];
		for (int i = 0; i < size_memory; i++) A[i] = r[i];
		return *this;
	};
	~Array() {
		delete[]A;
	}
	void insert(const T& value) {
		if (_size >= size_memory)
		{
			int i;
			T* C = new T[size_memory * 2];
			for (i = 0; i < _size; i++) C[i] = std::move(A[i]);
			delete[]A;
			A = new T[size_memory * 2];
			A = std::move(C);
			//for (i = _size; i < size_memory*2; i++) A[i] = NULL;
			size_memory = size_memory * 2;

		};
		A[_size] = value;
		_size++;
	};
	void insert(int index, const T& value) {
		Iterator b = iterator();
		b.toIndex(index);
		b.insert(value);
	};
	void remove(int index) {
		int i;
		for (i = index; i < _size; i++) {
			A[i] = A[i + 1];
		}
		A[i + 1] = NULL;
		_size--;
	};
	int size() {
		return _size;
	};
	T& operator [](int index) {
		return A[index];
	};
	Iterator iterator() {
		return Iterator(this);
	};
	void print() {
		for (int i = 0; i < _size; i++) {
			std::cout << A[i] << '\n';
		}
	}
};