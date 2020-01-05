//
// pch.h
// Header for standard system include files.
//

#pragma once

#include "gtest/gtest.h"
#include "pch.h"
#include "windows.h"
#include <iostream>
struct block {
	bool free;
	block*next;
	int size;
	void* mem;
	int flag;
};
struct DifPage {
	int countblock, countfreeblock, memory = 8192;
	void* memorypage;
	block *Current;
	DifPage(void *p) {
		Current = (block*)p;
		Current->size = sizeof(block);
		Current->free = true;
		Current->flag = 1;
		countblock = 0;
		countfreeblock = 0;
	};
	void Init(void *memo) {
		memorypage = memo;
		Current->next = (block*)memorypage + Current->size;
	};
	block* firstfit(int _size) {
		block *b = Current;
		while (b->next->next) {
			if (b->next->size >= _size) return(b->next);
			b = b->next;
		}
		return b;
	};
	block* newBlock(block* s, int _size) {
		block* a = (block *)VirtualAlloc(s->next, sizeof(block) + _size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		a->mem = a + sizeof(block);
		a->size = _size;
		a->next = a + a->size + sizeof(block);
		a->flag = 1;
		s = a->next;

		countblock++;
		memory = memory - _size - sizeof(block);
		return(a);
	};
	void* AllockBlock(int _size) {
		block* a = firstfit(_size);
		if (!(a->next->next)) return(newBlock(a->next, _size)->mem);
		else {
			block *b = a->next;
			if (a->next->next) a->next = a->next->next;
			countfreeblock--;
			return(b->mem);
		};
	};
	void deleteblock(void* b) {
		block* p = (block*)b - sizeof(block);
		if (!(merge(p))) {
			p->next = Current->next;
			Current->next = p;
		}
		countfreeblock++;
	}
	bool merge(block* b) {
		block *a = Current;

		while (a->next->next) {
			if (a->next + a->next->size == b) {
				a->next->size += b->size;
				countblock--;
				countfreeblock--;
				return true;
			}
			if (b + b->size == a->next) {
				b->size = b->size + a->next->size;
				a->next = a->next->next;
				countblock--;
				countfreeblock--;
				return false;
			}
			a = a->next;
		};
		return false;
	};
	void print() {
		std::cout << "not fix allocator\n";
		std::cout << " count free block= " << countfreeblock << " count adding block= " << countblock << " free memory= " << memory << '\n';
	}
};
struct MyPage {
	int _size;
	int countfreeblock, countblock, allblock;
	void* memorypage;
	block*Current;
	MyPage(int size) {
		_size = size;
		allblock = 4096 / _size;
		countblock = 0;
		countfreeblock = 0;
	};
	void Init(void *p) {
		memorypage = p;
		Current = (block*)memorypage;
		countblock = 0;
	};
	void newBlock() {
		Current->next = Current + _size + sizeof(block);
		Current->flag = 0;
		Current->free = true;
		Current->size = _size;
		Current->mem = Current + sizeof(block);
		countblock++;
		countfreeblock++;
	};
	void *AllocBlock() {
		block*a = Current;
		if (!(Current->next)) newBlock();
		a->free = false;
		countfreeblock--;

		Current = Current->next;
		return(a->mem);
	}
	void DeleteBlock(void* a) {
		block* p = (block *)a - sizeof(block);

		p->free = true;
		p->next = Current;
		*(int*)p = 0;
		Current = p;
		countfreeblock++;
	}
	void print() {
		std::cout << "fix allocator with size =" << _size << '\n';
		std::cout << "count adding block " << countblock << " count free block " << countfreeblock << '\n';
	};
};


class MyAllocator {
	DifPage pt;
	MyPage p[5];
	void* Base = VirtualAlloc(NULL, 1024 * 1024, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	int*  a = (int*)Base;

	int allsize = 0;
public:
	void* addmem(int size) {
		a = a + size;
		allsize += size;
		return (a - size);
	};
	struct statblock {
		block* cur;
		statblock*ptr;
		void addelem(block* newblock, void *lmem) {

			statblock *temp = (statblock*)lmem, *p = ptr;
			ptr = temp;
			temp->cur = newblock;
			temp->ptr = p;
		}
	} *sb = (statblock*)addmem(sizeof(statblock));

public:
	MyAllocator() : p{ MyPage(16),MyPage(32),MyPage(64),MyPage(128),MyPage(256) }, pt(VirtualAlloc(NULL, sizeof(block), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE)) {
		sb->cur = (block*)(addmem(sizeof(block)));
		sb->ptr = nullptr;

		//a = a + 2 * sizeof(block);
		//allsize += 2 * sizeof(block);
	};
	int recognize(int a) {
		for (int i = 0; i < 5; i++) {
			if (a <= pow(2, 4 + i))return i;
		}
		if (a > 256) return 20;
		if (a > 83886080) return 1000;
	};
	void Init() {
		for (int i = 0; i < 5; i++) p[i].Init(addmem(1024 * 4));
		pt.Init(addmem(1024 * 20));

	}
	void * alloc(int _size) {

		int l = recognize(_size);
		if (l < 5) {
			if (p[l].allblock == (p[l].countblock - p[l].countfreeblock)) {
				p[l].Init(addmem(1024 * 4));
			};
			void *c = p[l].AllocBlock();
			sb->addelem((block*)c - sizeof(block), addmem(sizeof(statblock)));
			return c;
		}
		if (l == 20) {
			if ((pt.memory < 512) && (pt.countfreeblock == 0)) pt.Init(addmem(1024 * 20));
			void *c = pt.AllockBlock(_size);
			sb->addelem((block*)c - sizeof(block), addmem(sizeof(statblock)));
			return c;
		};
		if (l == 1000) {
			block *l = (block*)(addmem(_size + sizeof(block)));
			l->size = _size;
			l->flag = 2;
			l->free = false;
			l->mem = l + sizeof(block);

			sb->addelem((block*)l, addmem(sizeof(statblock)));
			return(l->mem);

		};
	};

	void free(void* ps) {
		block* b = (block *)ps - sizeof(block);
		switch (b->flag) {
		case 0: p[recognize(b->size)].DeleteBlock(ps); break;
		case 1:	 pt.deleteblock(ps); break;
		case 2:  VirtualFree(ps, 0, MEM_RELEASE); break;
		};
	};
	void destroy() {
		VirtualFree(Base, 0, MEM_RELEASE);
	};
	void print() {
		pt.print();
		p[0].print();
	};
	void dumpBlocks() {
		std::cout << "list not empty block\n";
		statblock *l = sb;
		while (l != nullptr) {
			std::cout << "address: " << l->cur << " size: " << l->cur->size << '\n';
			l = l->ptr;
		};
	};
	void dumpStats() {
		std::cout << "Allocator's statistic:\n";
		for (int i = 0; i < 5; i++) p[i].print();
		pt.print();
		std::cout << "all size of allocator: " << allsize << '\n';
	};
};
/*int main()
{
	/*  std::cout << "Hello World!\n";
	  MyPage Page(sizeof(int));
	  int *p = (int*)Page.AllocBlock();
	  *p = 4;
	  Page.newBlock();
	  int  *t = (int*)Page.Current;
	  *t = 5;
	  Page.newBlock();
	  int  *t2 = (int*)Page.Current;
	  *t2 = 51;
	  Page.DeleteBlock(t);

	MyAllocator allo;
	allo.Init();
	std::cout << allo.recognize(222) << '\n';
	int *f = (int*)allo.alloc(sizeof(int));
	*f = 16;

	int *f2 = (int*)allo.alloc(sizeof(int));
	*f2 = 17;
	int *f3 = (int*)allo.alloc(sizeof(int));
	*f3 = 18;

	//std::cout << *p<<' '<<*t<<' '<<*f<<' '<<*f2<<' '<<*f3<<'\n';
	*f3 = 54;
	int *f4 = (int*)allo.alloc(sizeof(int));
	*f4 = 20;

	int *f5 = (int*)allo.alloc(sizeof(int));
	*f5 = 48;
	allo.free(f2);

	double* k = (double*)allo.alloc(sizeof(double));
	*k = 5.87;
	allo.free(k);

	int *p3 = (int*)allo.alloc(sizeof(int) * 100);
	for (int i = 0; i < 5; i++) *(p3 + i) = 6 + i;
	int *p4 = (int*)allo.alloc(sizeof(int) * 200);
	//allo.print();
	allo.free(p3);
	int *p2 = (int*)allo.alloc(sizeof(int) * 10);
	*p2 = 76;
	allo.free(p2);
	//	std::cout << *p << ' ' << *t << ' ' << *f << ' ' << *f2 << ' ' << *f3 << '\n';
		//allo.print();
		//std::cout << (sizeof(int) * 10) <<' '<< sizeof(*p3) <<' '<< sizeof(char);

	/*	DifPage Dif(VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));
		Dif.Init(VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));
		int *p1 = (int*)Dif.AllockBlock(sizeof(int)*100);
		*p1 = 47;

		std::cout << "dif " << *p1 << '\n';
		int *p2 = (int*)Dif.AllockBlock(sizeof(int)*100);
		*p2 = 76;
		/*
		Dif.deleteblock(p2);
		std::cout << "dif " << *p1 << ' ' << *p2 << '\n';
		//Dif.deleteblock(p2);
		double *p22 = (double*)Dif.AllockBlock(sizeof(double));
		*p22 = 7.89;
		//Dif.deleteblock(p22);
		std::cout << "dif " << *p1 << ' ' << *p2 << ' ' << *p22 << '\n';*/
		/*double *p4 = (double*)Dif.AllockBlock(sizeof(double));
		*p4 = 86.78;
		std::cout << "dif " << *p1 << ' ' << *p2 << ' ' << *p22 <<' '<< *p4<< '\n';
		int *p3 = (int*)Dif.AllockBlock(sizeof(int)*100 );
		for (int i = 0; i < 5; i++) *(p3+i) = 56+i;
		std::cout << "dif " << *p1 << ' ' << *p2 << ' ' << p3 << '\n';
		Dif.deleteblock(p3);*/
		/*
		  int *p5 = (int*)Dif.AllockBlock(sizeof(int));
		  *p5 = 88;
		  std::cout << "dif " << *p1 << ' ' << *p2 << ' ' << p3 <<*p4<<' '<<*p5<< '\n';


		  Dif.deleteblock(p5);
		  double *p6 = (double*)Dif.AllockBlock(sizeof(double));
		  *p6 = 2.76;
		  char *p7 = (char*)Dif.AllockBlock(sizeof(char));
		  *p7 = 't';
		  Dif.deleteblock(p3);
		  std::cout << p6;
		  Dif.deleteblock(p6);
		  //Dif.deleteblock(p1);
		  std::cout << "dif " << *p1 << ' '<<*p2<<' '<<p3<<' '<<*p4<<' '<<*p5<<' '<<*p6<<' '<<*p7<<'\n';
		  Dif.print();
		  
	allo.dumpStats();
	allo.dumpBlocks();
	allo.destroy();
}*/
