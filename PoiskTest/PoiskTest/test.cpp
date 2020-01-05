#include "pch.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TestCaseName1, TestName1) {
	EXPECT_EQ(1, 1);
	Dictionary<int, int> npc;
	//npc.remove(5);
	npc.put(1, 10);
	npc.put(16, 20);
	npc.put(3, 30);
	npc.put(7, 98);
	npc.put(7, 8);
	npc.put(9, 9);
	npc.remove(16);
	std::cout << npc[9] << '\n';
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
	it = npc.iterator();
	std::cout << it.key() << ' ' << it.get() << std::endl;
	it.next();
	std::cout << it.key() << ' ' << it.get() << std::endl;
	it.next();
	std::cout << it.key() << ' ' << it.get() << std::endl;
	it.next();
	std::cout << it.key() << ' ' << it.get() << std::endl;
	it.next();
	std::cout << it.key() << ' ' << it.get() << std::endl;
	if (it.hasNext()) std::cout << "zasada";
	EXPECT_TRUE(true);
}

TEST(TestCaseName2, TestName2) {
	EXPECT_EQ(1, 1);
	Dictionary<std::string, int > npc4;
	npc4.put("health", 10);
	npc4.put("armor", 20);
	npc4.put("ammo", 5);
	for (auto it = npc4.iterator(); it.hasNext(); it.next())
		std::cout << it.key() << ' ' << it.get() << std::endl;
	std::cout << npc4["armor"] << '\n';
	npc4.remove("health");
	npc4.put("armor", 144);
	for (auto it = npc4.iterator(); it.hasNext(); it.next())
		std::cout << it.key() << ' ' << it.get() << std::endl;
	EXPECT_TRUE(true);
}
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}