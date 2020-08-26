#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
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
#pragma comment(linker, "/STACK:66777216")

using namespace std;

template <class T>
class segment_tree 
{

public:

	segment_tree(int sz)
	{
		tree.resize(sz * 5, NODE(0, 0, 0));
		build(0, sz, &tree[0]);
	}

	void add_one_value(int pos, T value)
	{
		add_on_segment(pos, pos, value, &tree[0]);
	}

	void add_on_segment(int l, int r, T value)
	{
		add_on_segment(l, r, value, &tree[0]);
	}

	T sum(int l, int r)
	{
		return sum(l, r, &tree[0]);
	}


	void clear()
	{
		for (int i = 0; i < tree.size(); i++)
			tree[i].clear();
	}

private:
	struct NODE {
		T value;
		T node_sum;
		//T prop_value;
		int d_l, d_r;
		NODE* l;
		NODE* r;
		NODE(T value, int d_l, int d_r, NODE* l = nullptr, NODE* r = nullptr) :value(value), d_l(d_l), d_r(d_r), l(l), r(r), node_sum(0){}
		void clear()
		{
			value = 0;
			node_sum = 0;
			d_l = 0;
			d_r = 0;
			l = nullptr;
			r = nullptr;
		}
	};


	vector<NODE> tree;
	int pos_in_tree_arr = 0;
	NODE* build(int l, int r, NODE* node, T default_value = 0)
	{
		node->value = default_value;
		node->d_l = l;
		node->d_r = r;
		if (l != r) 
		{
			int new_ll = l;
			int new_lr = (l + r) / 2;
			pos_in_tree_arr++;
			node->l = build(new_ll, new_lr, &tree[pos_in_tree_arr], default_value);
			int new_rl = new_lr + 1;
			int new_rr = r;
			pos_in_tree_arr++;
			node->r = build(new_rl, new_rr, &tree[pos_in_tree_arr], default_value);
		}
		return node;
	}



	T add_on_segment(int l, int r, T value, NODE* node)
	{
 		if (l == node->d_l && r == node->d_r)
		{
			node->value += value;
			node->node_sum += value * (r - l + 1);
		}
		else
		{
			if (node->l->d_r >= l)
			{
				node->node_sum -= node->l->node_sum;
				node->node_sum += add_on_segment(l, min(node->l->d_r, r), value, node->l);
			}
			if (node->r->d_l <= r)
			{
				node->node_sum -= node->r->node_sum;
				node->node_sum += add_on_segment(max(node->r->d_l, l), r, value, node->r);
			}
		
		}
		return node->node_sum;
	}

	T sum(int l, int r, NODE* node)
	{
		T res = (r - l + 1) * node->value;
		if (l == node->d_l && r == node->d_r)
		{
			return node->node_sum;
		}
		else
		{
			if (node->l->d_r >= l)
			{
				res += sum(l, min(node->l->d_r, r), node->l);
			}
			if (node->r->d_l <= r)
			{
				res += sum(max(node->r->d_l, l), r, node->r);
			}
		}
		return res;
	}


};


int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	segment_tree<int> tree(1000000);
	


	tree.add_one_value(1, 100);
	tree.add_one_value(10, 50);
	tree.add_one_value(20, 30);
	cout << tree.sum(1, 100) << ' ';
	tree.add_on_segment(50, 100, 100);
	cout << tree.sum(1, 100) << ' ';
	cout << tree.sum(1, 50) << ' ';
	cout << tree.sum(75, 76) << ' ';
	tree.add_on_segment(20, 27, 2);
	cout << tree.sum(26, 27) << ' ';
	cout << tree.sum(20, 20) << ' ';

}