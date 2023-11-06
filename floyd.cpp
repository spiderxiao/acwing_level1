#include <iostream>
#include <cmath>

using namespace std;

const int N = 210;

int n, m, Q;
int d[N][N];


//基于动态规划的算法
void floyd()
{
    /*
    floyd本身是个动态规划算法，在代码实现的时候省去了一维状态。
原状态是：f[i, j, k]表示从i走到j的路径上除了i, j以外不包含点k的所有路径的最短距离。
那么f[i, j, k] = min(f[i, j, k - 1), f[i, k, k - 1] + f[k, j, k - 1]。
因此在计算第k层的f[i, j]的时候必须先将第k - 1层的所有状态计算出来，所以需要把k放在最外层。
    */
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}

int main()
{
    cin >> n >> m >> Q;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            //把i == j的位置赋值为0，是为了保证没有环
            if (i == j) d[i][j] = 0;
            //把其他位置赋值为INF是为了保证后续只保留最短的重边
            else d[i][j] = 0x3f3f3f3f;
        }
    }

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        d[a][b] = min(d[a][b], c);
    }

    floyd();

    while (Q--)
    {
        int a, b;
        cin >> a >> b;

        if (d[a][b] > 0x3f3f3f3f / 2) cout << "impossible" << endl;
        else cout << d[a][b] << endl;
    }
    return 0;
}