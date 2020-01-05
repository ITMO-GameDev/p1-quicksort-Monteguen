//
// pch.h
// Header for standard system include files.
//

#pragma once

#include "gtest/gtest.h"
// Poisk_Lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

template < typename K, typename V>
struct data {
public:
	K key;
	V value;
	data() {};
	data(K a, V b) :key(a), value(b) {};
};


template < typename K, typename V>
class BRTree {



public:
	struct node {
		node *L;
		node *R;
		node *P;
		bool isRed;
		data<K, V> D;
	};
#define NIL &s
	node s = { NIL,NIL,0,false,};
	node *root;
	BRTree() {
		root = NIL;
	};
	BRTree& operator = (BRTree &_t) {

	};
	~BRTree() {
		this->destroy(root);
	};
	void RotateL(node *x) {
		node *y = x->R;
		x->R = y->L;
		if (y->L != NIL) y->L->P = x;

		if (y != NIL) y->P = x->P;
		if (x->P) {
			if (x == x->P->L)
				x->P->L = y;
			else
				x->P->R = y;
		}
		else {
			root = y;
		}

		y->L = x;
		if (x != NIL) x->P = y;
	};

	void RotateR(node *x) {
		node *y = x->L;
		x->L = y->R;
		if (y->R != NIL) y->R->P = x;

		if (y != NIL) y->P = x->P;
		if (x->P) {
			if (x == x->P->L)
				x->P->L = y;
			else
				x->P->R = y;
		}
		else {
			root = y;
		}

		y->R = x;
		if (x != NIL) x->P = y;
	};
	node* uncle(node *x) {
		if (x->P->P->L == x->P) return x->P->P->R;
		else return (x->P->P->L);
	};

	void insertFix(node *x) {
		while ((x != root) && (x->P->isRed)) {
			node* z = uncle(x);
			if (z->isRed) {
				x->P->isRed = false;
				z->isRed = false;
				x->P->P->isRed = true;
				x = x->P->P;
			}
			else {
				if (x->P->P->L == x->P) {
					if (x->P->R == x) {
						x = x->P;
						RotateL(x);
					}
					x->P->isRed = false;
					x->P->P->isRed = true;
					RotateR(x->P->P);
				}
				else {
					if (x->P->L == x) {
						x = x->P;
						RotateR(x);
					}
					x->P->isRed = false;
					x->P->P->isRed = true;
					RotateL(x->P->P);
				};
			};
		};
		root->isRed = false;
	};

	void insertNode(data<K, V> newData) {

		node *current, *parent, *x;
		current = root;
		parent = 0;
		while (current != NIL) {
			data<K, V> p = current->D;
			//if (newData.key == p.key) return (5);
			parent = current;
			if (newData.key < current->D.key) current = current->L;
			else current = current->R;
		}
		x = new node{ NIL,NIL,parent,true,newData };
		if (parent) {
			if (newData.key < parent->D.key) parent->L = x;
			else  parent->R = x;
		}
		else root = x;

		insertFix(x);
		//return(x->D.key);
	};
	void deleteFix(node *child) {

		while ((child != root) && (child->isRed = false)) {
			node  *parent = child->P, *sibling = parent->L == child ? parent->R : parent->L;
			bool fl = (parent->R == sibling);
			if (sibling->isRed) {
				if (fl) RotateR(parent); else RotateL(parent);
				sibling->isRed = false;
				parent->isRed = true;
			}
			else {
				if (!(sibling->R->isRed) && !(sibling->L->isRed)) {
					sibling->isRed = false;
					child = parent;
				}
				else if ((sibling->L->isRed) && !(sibling->R->isRed)) {
					sibling->isRed = false;
					sibling->L->isRed = false;
					if (fl) RotateR(sibling); else RotateL(sibling);
				}
				else if (sibling->R->isRed) {
					sibling->isRed = parent->isRed;
					if (fl) RotateR(parent); else RotateL(parent);
					return;
				};
			}
		}
		child->isRed = false;
	};
	void deleteNode(node *x) {
		node *y, *z;
		if (x == NIL) return;
		if ((x->L == NIL) || (x->R == NIL)) y = x;
		else {
			y = x->R;
			while (y->L != NIL) y = y->L;
		};
		if (y->L != NIL)
			z = y->L;
		else
			z = y->R;

		z->P = y->P;

		if (y->P)
			if (y == y->P->L)
				y->P->L = z;
			else
				y->P->R = z;
		else
			root = z;


		if (y != x) x->D = y->D;


		if (y->isRed == false)
			deleteFix(z);
		delete y;
	};
	node* findNode(data<K, V> d) {
		node *current = root;
		while (current != NIL) {
			if (d.key == current->D.key) return (current);
			else current = (d.key < current->D.key) ? current->L : current->R;
		}
		return(0);
	};

	bool exsitNode(data<K, V> d) {
		node *current = root;
		while (current != NIL) {
			if (d.key == current->D.key) return (true);
			else current = (d.key < current->D.key) ? current->L : current->R;
		}
		return(false);
	};

	void print(node* x) {
		if (x != NIL) std::cout << x->D.key << '\n';
	};
	/*void obhod(node* k) {
		if (k == NIL) return;
		else {
			print(k);
			obhod(k->L);
			obhod(k->R);
		}
	};*/
	node* min(node* k) {
		while (k->L != NIL) k = k->L;
		return k;
	};
	node* max(node* k) {
		while (k->R != NIL) k = k->R;
		return k;
	};

	node* next(node* Node) {
		node *y = NIL;
		if (Node->R != NIL) y = min(Node->R);
		else {
			y = Node;
			while (y->P) {
				if (y == y->P->L) { y = y->P; break; };
				y = y->P;
			}
		};
		//if (Node == y) return(NIL);
		return(y);
	};

	node* prev(node* Node) {
		node *y = NIL;
		if (Node->L != NIL) y = max(Node->L);
		else {
			y = Node;
			while (y->P) {
				if (y == y->P->R) { y = y->P; break; };
				y = y->P;
			}
		};
		//if (Node == y) return(NIL);
		return(y);
	};

	/*node* prev(node* Node) {
		node *y = Node->P;

		if (Node->L != NIL)	y = max(Node->L);
		else {
			while ((y != NIL) && (y == (y->P->L))) y = y->P;
		};
		return(y);
	};*/

	bool hasPrev(node* Node) {
		return (Node != prev(Node));
	};
	void destroy(node* k) {
		if (k == NIL) return;
		else {
			destroy(k->L);
			destroy(k->R);
			delete k;
		};
	};
};

template < typename K, typename V>
class Dictionary {

	BRTree<K, V>* _tree;

	data<K, V> *masD;
	int _size;
public:
	class Iterator {
		BRTree<K, V>* pTree;
		typename BRTree<K, V>::node *Node;
		int iter;
		int ssize;
	public:
		Iterator(Dictionary<K, V>*_pTree) :pTree(_pTree->_tree) {
			Node = pTree->min(pTree->root);
			iter = 0;
			ssize = _pTree->size();
		};
		const K& key() {
			return Node->D.key;
		};
		const V& get() {
			return Node->D.value;
		}
		void set(const V& value) {
			Node->D.value = value;
		}
		void next() {
			Node = pTree->next(Node);
			iter++;
		};
		void prev() {
			Node = pTree->prev(Node);
			iter--;
		};
		bool hasNext() {
			//std::cout << iter << ' ' << ssize << '\n';
			return (iter < ssize);
		};

		bool hasPrev() {
			return (iter > 0);
		};
	};
	Dictionary() {
		masD = new data<K, V>;
		_tree = new BRTree<K, V>;

		_size = 0;
	};
	~Dictionary() {
		delete masD;
		delete _tree;
	};
	Dictionary(Dictionary& Dic) {

		//_tree->destroy(_tree->root);
		_tree = new BRTree<K, V>;
		masD = new data<K, V>(0, 0);
		_size = 0;
		for (auto it = Dic.iterator(); it.hasNext(); it.next()) {
			this->put(it.key(), it.get());
		};

	};
	Dictionary& operator = (Dictionary &Dic) {
		_tree->destroy(_tree->root);
		_tree = new BRTree<K, V>;
		_size = 0;
		for (auto it = Dic.iterator(); it.hasNext(); it.next()) {
			this->put(it.key(), it.get());
		}
		return *this;
	};
	V& operator [](const K& key) {
		*masD = data<K, V>(key, 0);
		if (!_tree->exsitNode(*masD)) this->put(key, 0);
		return(_tree->findNode(*masD)->D.value);

	};
	void put(const K& key, const V& value) {
		std::cout << "V\n";
		*masD = data<K, V>(key, value);
		if (_tree->exsitNode(*masD)) _tree->findNode(*masD)->D.value = value;
		else {
			_tree->insertNode(*masD);
			_size++;
		};
	};
	void remove(const K& key) {
		*masD = data<K, V>(key, 0);
		if (_tree->exsitNode(*masD)) {
			_tree->deleteNode(_tree->findNode(*masD));
			_size--;
		};
	};
	bool contains(const K& key) {
		*masD = data<K, V>(key, 0);
		return _tree->exsitNode(*masD);
	};
	int size() {
		return _size;
	};
	Iterator iterator() {
		return Iterator(this);
	};

};

/*int main()
{
	std::cout << "Hello World!\n";
	/*	BRTree<int,int> t;
		data<int, int> a(35, 7), v(51, 32), u(9, 11), iu(16, 78);
		int y= t.insertNode(a);
		y = t.insertNode(v);
		//y = t.insertNode(u);
		//y = t.insertNode(data<int, int>(7,15));
		y = t.insertNode(data<int, int>(78, 5));
		y = t.insertNode(data<int, int>(19, 65));
		y = t.insertNode(data<int, int>(25, 5));
		y = t.insertNode(data<int, int>(2, 5));
		y = t.insertNode(data<int, int>(6, 95));
		y = t.insertNode(data<int, int>(45, 5));
		y = t.insertNode(data<int, int>(66, 566));
		y = t.insertNode(data<int, int>(116, 5));
		y = t.insertNode(data<int, int>(-7, 5));
		t.print(t.max(t.root) );
		t.print(t.findNode(a));
		t.deleteNode(t.findNode(a));
		/*t.print(t.findNode(a));
		//t.destroy(t.root);
		//if (t.findNode(u)) std::cout << "sush";
	Dictionary<int, int> npc;
	//npc.remove(5);
	npc.put(1, 10);
	npc.put(16, 20);
	npc.put(3, 30);
	npc.put(7, 98);
	npc.put(7, 8);
	npc.put(9, 9);
	//npc.remove(3);
	auto it = npc.iterator();
	for (it; it.hasNext(); it.next())
		std::cout << it.key() << ' ' << it.get() << std::endl;
	Dictionary<int, int> npc2;
	npc2.put(7, 7);
	npc2.put(45, 67);
	npc2.put(78, 79);
	//npc = npc2;
	Dictionary<int, int> npc3(npc2);
	it = npc3.iterator();
	for (it; it.hasNext(); it.next())
		std::cout << it.key() << ' ' << it.get() << std::endl;
	auto it = npc.iterator();
	std::cout << it.key() << ' ' << it.get() << std::endl;
	it.next();
	std::cout << it.key() << ' ' << it.get() << std::endl;
	it.next();
	std::cout << it.key() << ' ' << it.get() << std::endl;
	it.next();
	std::cout << it.key() << ' ' << it.get() << std::endl;
	it.next();
	std::cout << it.key() << ' ' << it.get() << std::endl;
	if (it.hasNext()) std:: cout <<"zasada";
}*/
