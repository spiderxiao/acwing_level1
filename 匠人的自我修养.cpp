#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;

//用邻接表来实现图的构建
int h[N], e[N], ne[N], idx;
int n, m;
int spend[N], gain[N];
bool st[N];
int cnt;
void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

//判断是否可以用，可以用的条件是把前置条件全学了
bool avalid(int q)
{
	for (int i = h[q]; i != -1; i = ne[i])
	{
		int j = e[i];
		if (!st[j]) return false;
	}
	return true;
}
void find()
{
	//因为当学习了一门技术后，可能之前不能学的技术可以学了，所以至少要遍历n遍，把所以技术遍历完
	for (int k = 1; k <= n; k++)
	{
		//每一次遍历所有技术
		for (int i = 1; i <= n; i++)
		{
			//只有没学过且能学，才学
			if (!st[i] && m >= spend[i] && avalid(i))
			{
				m += gain[i];
				cnt++;
				st[i] = true;
			}
		}
	}
}
int main()
{
	memset(h, -1, sizeof h);
	cin >> n >> m;

	for (int i = 1; i <= n; i++)
	{
		cin >> spend[i] >> gain[i];
	}

	//建图，把某一项技术需要的条件与其相连
	for (int i = 1; i <= n; i++)
	{
		int a = 0;
		cin >> a;
		for (int j = 0; j < a; j++)
		{
			int b = 0;
			cin >> b;
			add(i, b);
		}
	}
	find();
	cout << cnt << endl;

	return 0;
}