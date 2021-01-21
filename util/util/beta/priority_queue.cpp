#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;
int mainxx()
{
	// 使用优先级队列实现最大堆最小堆：时间复杂度有O(logK)。
	// https://blog.csdn.net/nisxiya/article/details/45725857
	// http://www.sobugou.com/blog/2015/09/01/hashmapshi-li-:qiu-top-k/
	unordered_map<int, int> map = { {1,1},{3,3},{2,2},{4,4},{5,5},{7,7},{6,6} };
	struct node {
		int userid;
		int deposit;
		node(int a = 0, int b = 0) :userid(a), deposit(b) {}
	};

	struct cmp {
		bool operator()(node a, node b) {
			return a.deposit > b.deposit;
		}
	};
	priority_queue<node, vector<node>, cmp> q;
	q.push(node(0, 0));
	q.push(node(0, 0));
	q.push(node(0, 0));
	for (const auto& v : map)
	{
		std::cout << "q.top() is now " << q.top().userid << " " << q.top().deposit << '\n';
		if (v.second > q.top().deposit)
		{
			q.pop();
			q.push(node(v.first, v.second));
		}
	}
	return 0;
}