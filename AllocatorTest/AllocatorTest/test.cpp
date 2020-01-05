#include "pch.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TestCaseName2, TestName2) {
	EXPECT_EQ(1, 1);
	std::cout << "dfsfd\n";
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
	allo.dumpStats();
	allo.dumpBlocks();
	allo.destroy();
	EXPECT_TRUE(true);
}
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}