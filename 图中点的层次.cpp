#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;

int h[N], ne[N], e[N], idx;
int q[N];//模拟栈
int d[N];//编号为n的结点到起点的距离
int n, m;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int bfs()
{
    memset(d, -1, sizeof d);//用来标记最开始所有店没有走过

    q[0] = 1;//因为起点肯定是1， 所以最开始栈中第 ‘0’ 点的编号 为1
    d[1] = 0;//起点为1，所以编号为1的点到起点的距离为1
    int hh = 0, tt = 0;//栈头和栈尾

    while (hh <= tt)
    {
        int t = q[hh++];//取出栈头
        for (int i = h[t]; i != -1; i = ne[i])//遍历这条支路
        {
            //取出编号(idx)为i的结点中存的值 (n)
            int j = e[i];
            //没有遍历过
            if (d[j] == -1)
            {
                //因为这条支路上的所有点都是直接为t这个结点相连的，所以距离都只相差1
                d[j] = d[t] + 1;
                //支路上的所有结点进栈
                q[++tt] = j;
            }
        }

    }

    return d[n];
}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    cout << bfs() << endl;
    return 0;
}
