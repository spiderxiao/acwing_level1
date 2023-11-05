#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int N = 510;

int g[N][N];//g[i][j]表示i点到j点的距离
int dist[N];//dist[i]表示i点到起点的最短距离
int n, m;
bool st[N];//st[i] = true表示i点的最短距离已经求出来了
int dijkstra()
{
    dist[1] = 0;//1为起点距离为0
    //需要遍历n - 1遍，每一遍只能求出一个点的最短距离，有n个点，第一个点不用求了所以是n - 1遍
    for (int i = 1; i < n; i++)
    {
        int t = -1;
        //每次需要找到距离起点最短的点且没被用过的点，用来更新一遍最短路径
        for (int j = 1; j <= n; j++)
        {
            if (!st[j] && (t == -1 || dist[t] > dist[j]))
            {
                t = j;
            }
        }
        //标记一下这个点被使用过了
        st[t] = true;
        //更新路径
        for (int j = 1; j <= n; j++)
        {
            dist[j] = min(dist[j], dist[t] + g[t][j]);

        }

    }
    if (dist[n] == 0x3f3f3f3f) return -1;
    else return dist[n];
}

int main()
{
    cin >> n >> m;


    memset(dist, 0x3f, sizeof dist);

    //把g数组赋值是为了只保流重边中的最短的边
    memset(g, 0x3f, sizeof g);
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = min(g[a][b], c);
    }
    cout << dijkstra() << endl;

    return 0;
}