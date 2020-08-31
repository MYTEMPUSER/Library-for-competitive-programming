#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <iostream>
#include <iostream>
#include <fstream>
#include "segment_tree.cpp"
#include "DSU.cpp"

#pragma comment(linker, "/STACK:66777216")

using namespace std;

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	segment_tree<int> tree(1000000);


	DSU dsu;
	vector<int> sets;
	for (int i = 0; i < 100; i++)
		sets.push_back(dsu.add_new_elem());

	for (int i = 0; i < 50; i++)
	{
		dsu.union_sets(sets[rand() % 100], sets[rand() % 100]);
		cout << dsu.is_in_one_set(sets[rand() % 100], sets[rand() % 100]) << endl;
	}
}