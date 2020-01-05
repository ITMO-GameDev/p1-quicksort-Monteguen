#include "pch.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  Array< int > a;
  for (int i = 0; i < 10; ++i)
	  a.insert(i);
  for (int i = 0; i < a.size(); ++i)
	  a[i] *= 2;
  for (auto it = a.iterator(); it.hasNext(); it.next())
	  std::cout << it.get() << std::endl;
  EXPECT_TRUE(true);
}

TEST(TestCaseName2, TestName2) {
	Array<int> B(4);
	B.insert(1);
	B.insert(2);
	B.insert(3);
	B.insert(4);
	B.insert(4875);
	B.insert(5);
	B.print();
	B.remove(4);
	B.print();
	for (int i = 0; i < 3; i++) B.remove(0);
	B.print();
	B.remove(0);
	B.remove(0);
	std::cout << B.size()<<'\n';
	for (int i = 0; i < 10; i++) B.insert(i+10*i);
	B.print();
	EXPECT_TRUE(true);
}

TEST(TestCaseName3, TestName3) {
	EXPECT_EQ(1, 1);
	Array<int> B(8);
	B.insert(1);
	B.insert(2);
	B.insert(3);
	B.insert(4);
	//std::cout << B.size();
	//B.print();
	Array<int>::Iterator iter = B.iterator();

	iter.next();
	iter.next();
	iter.next();
	std::cout << iter.get()<<'\n';
	iter.insert(87);
	iter.remove();
	iter.toIndex(2);
	std::cout << iter.get() << '\n';
	iter.set(76);
	std::cout << iter.get() << '\n';
	for (auto it = B.iterator(); it.hasNext(); it.next())
		std::cout << it.get() << std::endl;
	EXPECT_TRUE(true);
}

class Data {
public:
	std::string name;
	int num;
	Data() {};
	Data(std::string _name, int _num) :name(_name), num(_num) {};
};
TEST(TestCaseName4, TestName4) {
	EXPECT_EQ(1, 1);
	Array< Data > a;
	for (int i = 0; i < 10; ++i)
		a.insert(Data("pump",i));
	for (int i = 0; i < a.size(); ++i)
		a[i].num *= 2;
	for (auto it = a.iterator(); it.hasNext(); it.next())
		std::cout << it.get().num << std::endl;
	EXPECT_TRUE(true);
}
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}