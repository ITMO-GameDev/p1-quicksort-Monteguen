// ConsoleApplication5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
const int n = 10;
int A[n]=  { 7,5,5,5,2,7,5,4,5,7};
//int A[n] = {10,9,10,9,9,10,9,9,10,9};
//int A[n] = { 10,10,8,8,10,2,2,10,2,10 };
//int *A = new int[10] { 10,9,8,7,6,5,4,3,2,1 };
//int A[n] = { 1,2,3,4,5,6,7,8,9,10 };
//int B[5] = { 3,4,3,2,1 };


template <typename T>
void swap(T &a, T &b)
{
	T c = b;
	b = a;
	a = c;
}
int printup() {
	return 5;
}
template <typename T>
void printmas(T C[]) {
	for (int i = 0; i < n; i++)  std::cout << C[i] << "  ";
	std::cout << '\n';
}
template <typename T, typename Compare>
T *Mediana(T *a, T *b, T *c, Compare comp) {
	if (comp(*a,*b)) {
		if (comp(*b, *c)) return b; //a<b<c
		else if (comp(*a, *c)) return c; //a<c<b
		else return a; //c<a<b
	}
	else if (comp(*b,*a)) {
		if (comp(*a, *c)) return a; //b<a<c
		else if (comp(*b, *c)) return c; //b<c<a
		else return b; //c<b<a
	}
	//else if (*c != *b) return b;
	else return b;
}

template <typename T, typename Compare>
T *testfindpivot(T *i, T *j, Compare comp) {
	T firstkey = *i;
	for (T *k = i ; k < j; ) {
		k++;
		if (comp(firstkey, *k)) return k;
		if (comp(*k, firstkey)) return i;
	}
	return 0;
}

template <typename T, typename Compare>
T *testpartion(T *i, T *j, T pivot, Compare comp) {
	T *l = i, *r = j;
	while (l <= r) {
	//std::cout << "l=" << *l << "r=" << *r << "pivot=" << pivot << '\n';

		while (comp(*l, pivot)&&(l<j)) l++;
		while (comp(pivot,*r)&&(r>i)) r--;
		if (l > r) return l;
		swap(*l, *r);
		l++; r--;
	 };
	 return l;
}

template <typename T>
void lenpart(T a, T b, T c, T &d1, T &e1) {
	int p1 = b - a, p2 = c - b;
	if (p1 < p2) { d1 = a; e1 = b - 1; }
	else { d1 = b; e1 = c; };
}
template <typename T, typename Compare >
void insersort(T *f, T *g, Compare comp) {

	T *l = f, *t = f, *r = g;
	while (l< r) {
		l++;
		t = l;
		while ((t > f)&&comp(*(t), *(t - 1))) {
			swap(*(t - 1), *t);
			t--;
		}
	}
}
template <typename T, typename Compare >
void testsort(T *f, T *g, Compare comp) {
	if ((g-f)<3) insersort(f, g, comp);
	else {
//	for (T* i = f; i < g; i++) std::cout << *i << ' ';
//	std::cout << '\n';
		T *p = f+((int(g - f)) / 2);
		T *t = Mediana(f, g, p,comp ), *t1, *a1 = f, *b1 = g;
		T *t2 = testfindpivot(f, g, comp);

		if ((t2 != 0) && (f < g)) {

			t1 = testpartion(f, g, *t, comp);
			/*for (T* i = f; i < g; i++) std::cout << *i << ' ';
			std::cout << '\n';*/

			lenpart(f, t1, g, a1, b1);

			testsort(a1, b1, comp);
			testsort(f - a1 + t1, g - b1 + (t1 - 1), comp);
		};
	}
}
class Data {
public:
	std::string name;
	int num;
	Data() {};
	Data(std::string _name, int _num) :name(_name), num(_num) {};
};
template Temp2<Data>;
template Temp2<int>;
template Temp2<double>;
template <typename T>
Temp2<T>::Temp2(T *a1,T *b1, bool(*func)(T a, T b) ){
	testsort(a1, b1, func);
};
