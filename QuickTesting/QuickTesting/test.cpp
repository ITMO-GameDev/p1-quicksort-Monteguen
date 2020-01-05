#include "pch.h"

TEST(TestCaseName, TestName1) {
	int n1 = 10;
	int *mas1 = new int[n1]{ 10,9,8,7,6,5,4,3,2,1 };
	int *mas11 = new int[n1] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	
	Temp2<int> temp2(mas1,mas1+n1-1,
		[](int a,int b) {

		return a < b;
		 }
	);
	//Templ<int> templ(mas1, n1);
	for (int i = 0; i < n1; i++) {
		ASSERT_EQ(mas1[i], mas11[i]);
	}
}


TEST(TestCaseName2, TestName1) {
	int n2 = 10;
	int *mas2 = new int[n2] { 1,2,3,4,5,6,7,8,9,10 };
	int *mas22 = new int[n2] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	Temp2<int> temp2(mas2, mas2 + n2 - 1,
		[](int a, int b) {

		return a < b;
	}
	);
	//Templ<int> templ(mas2, n2);
	for (int i = 0; i < n2; i++) {
		ASSERT_EQ(mas2[i], mas22[i]);
	}
}

TEST(TestCaseName3, TestName1) {
	int n3 = 10;
	int *mas3 = new int[n3] {1,10,10,5,10,10,5,5,5,5 };
	int *mas33 = new int[n3] { 1, 5, 5, 5, 5,5, 10, 10, 10, 10 };
	//Templ<int> templ(mas3, n3);

	Temp2<int> temp2(mas3, mas3 + n3 - 1,
		[](int a, int b) {

		return a < b;
	}
	);

	for (int i = 0; i < n3; i++) {
		ASSERT_EQ(mas3[i], mas33[i]);
	}
}

TEST(TestCaseName4, TestName1) {
	int n4 = 10;
	int *mas4 = new int[n4] {2,4,5,5,1,8,5,2,4,5 };
	int *mas44 = new int[n4] {1,2,2,4,4,5,5,5,5,8 };
	//Templ<int> templ(mas4, n4);

	Temp2<int> temp2(mas4, mas4 + n4 - 1,
		[](int a, int b) {

		return a < b;
	}
	);

	for (int i = 0; i < n4; i++) {
	//	std::cout << mas4[i] << '\n';
		ASSERT_EQ(mas4[i], mas44[i]);
	}
}
class Data {
public:
	std::string name;
	int num;
	Data() {};
	Data(std::string _name, int _num) :name(_name), num(_num) {};
};
TEST(TestCaseName5, TestName1) {
	int n1 = 5;
	double *mas1 = new double[n1] { 13.41,3.78,13.89,12.12345,1.67 };
	double *mas11 = new double[n1] {1.67,3.78,12.12345,13.41,13.89};

	Temp2<double> temp2(mas1, mas1 + n1 - 1,
		[](double a, double b) {

		return a < b;
	}
	);
	//Templ<int> templ(mas1, n1);
	for (int i = 0; i < n1; i++) {
		ASSERT_EQ(mas1[i], mas11[i]);
	}
}
TEST(TestCaseName6, TestName1) {
	int n1 = 5;
	Data *mas1 = new Data[n1] { Data("bubble",45), Data("bubble",56),Data("bubble",12),Data("bubble",98),Data("bubble",36) };
	Data *mas11 = new Data[n1] { Data("bubble",12), Data("bubble",36),Data("bubble",45),Data("bubble",56),Data("bubble",98) };

	Temp2<Data> temp2(mas1, mas1 + n1 - 1,
		[](Data a, Data b) {

		return a.num < b.num;
	}
	);
	//Templ<int> templ(mas1, n1);
	for (int i = 0; i < n1; i++) {
		ASSERT_EQ(mas1[i].num, mas11[i].num);
	}
}
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}