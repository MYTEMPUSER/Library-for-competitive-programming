#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <unordered_map>
#include <iostream>
#include <cctype>
#include <clocale>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <cassert>


using namespace std;


class DSU 
{
private:
	struct NODE {
		int val;
		int set_size;
		NODE* parent;
		NODE(int val, NODE* parent, int set_size = 0) : val(val), parent(parent), set_size(set_size) {}
	};
	vector<NODE> set_list;

	NODE* find_set(NODE* node)
	{
		if (node->parent != nullptr)
		{
			node->parent = find_set(node->parent);
			return node->parent;
		}
		else
			return node;
	}

public:

	DSU(){}

	DSU(int sz)
	{
		for (int i = 0; i < sz; i++)
			set_list.push_back(NODE(i, nullptr, 1));
	}

	int add_new_elem(NODE* parent = nullptr)
	{
		set_list.push_back(NODE(set_list.size(), parent));
		auto pointer = find_set(&set_list.back());
		pointer->set_size += 1;
		return set_list.size() - 1;
	}

	NODE* find_set(int pos)
	{
		return find_set(&set_list[pos]);
	}

	

	bool is_in_one_set (int set1, int set2)
	{
		return find_set(set1) == find_set(set2);
	}

	int union_sets(int set1, int set2)
	{
		auto p1 = find_set(set1);
		auto p2 = find_set(set2);
		if (!is_in_one_set(set1, set2))
		{
			if (p1->set_size < p2->set_size)
				swap(p1, p2);
			p1->parent = p2;
			p2->set_size += p1->set_size;
		}
		return int(p2);
	}

};


