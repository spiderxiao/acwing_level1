#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int N = 510;

int dist[N];//dist[i]表示i点到集合的最短
int g[N][N];//g[i][j]表示i到j的边的长度 没有直接相连则为0x3f3f3f3f
int n, m;
bool st[N];//标记是否已经加入了集合中

int prim()
{
    memset(dist, 0x3f, sizeof dist);

    int res = 0;

    //找到距离集合最近的一个点
    for (int i = 0; i < n; i++)
    {
        int t = -1;
        for (int j = 1; j <= n; j++)
        {
            if (!st[j] && (t == -1 || dist[t] > dist[j]))
            {
                t = j;
            }
        }

        //这里我们可以默认先将第 1 个点加入集合，如果不是第一个点且距离集合为0x3f3f3f3f则这个图不连通
        if (i && dist[t] == 0x3f3f3f3f) return 0x3f3f3f3f;

        //要把 res += dist[t]放在更新的前面，因为有负环的时候，会改变dist[t]
        if (i) res += dist[t];
        st[t] = true;

        //更新， 现在因为集合新加入了一个点，所以要判断当前点距离集合的距离是不是可以通过加入的
        //这个点来更新
        for (int j = 1; j <= n; j++)
        {
            dist[j] = min(dist[j], g[t][j]);
        }
    }
    return res;
}
int main()
{
    memset(g, 0x3f, sizeof g);

    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        //无向图，建立两条边，取min防止重边
        g[a][b] = g[b][a] = min(g[a][b], c);
    }

    int t = prim();
    if (t == 0x3f3f3f3f) cout << "impossible" << endl;
    else cout << t << endl;
    return 0;
}