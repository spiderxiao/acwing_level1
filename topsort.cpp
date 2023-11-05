#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;

int h[N], ne[N], e[N], idx;
int d[N], q[N];//入度， 栈
int n, m;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

bool topsort()
{
    int hh = 0, tt = -1;
    for (int i = 1; i <= n; i++)
    {
        if (d[i] == 0)//入度为0的点都可以是起点
        {
            q[++tt] = i;//入队
        }
    }

    while (hh <= tt)
    {
        int t = q[hh++];//出队

        for (int i = h[t]; i != -1; i = ne[i])//遍历i点的所有边
        {
            int j = e[i];
            d[j]--;//遍历过后要删除i点，即使得与i相连接的所有点的入度减一
            if (d[j] == 0)//删除i点后，入度为0的点可以作为一个新的起点
            {
                q[++tt] = j;
            }
        }
    }

    return tt == n - 1;//如果有环，图就删不完，那么tt != n - 1
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
        d[b]++;
    }
    if (topsort())
    {
        for (int i = 0; i < n; i++)
        {
            cout << q[i] << " ";
        }
        cout << endl;
    }
    else
    {
        cout << -1 << endl;
    }
    return 0;
}