#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int N = 110;
typedef pair<int, int> PII;//队列用来存储当前这一层遍历到的点

int d[N][N];//d[i][j]表示(i, j)点距离(0, 0)点的距离

//方向向量 上下左右
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int n, m;
int g[N][N];

int dfs()
{
    queue<PII> q;
    q.push({ 0, 0 });//第一个点(0, 0)
    d[0][0] = 0;

    while (q.size())
    {
        auto t = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int x = t.first + dx[i];
            int y = t.second + dy[i];

            if (x >= 0 && x < n && y >= 0 && y < m && d[x][y] == -1 && g[x][y] == 0)
            {
                d[x][y] = d[t.first][t.second] + 1;
                q.push({ x, y });//走到了(x,y)点之后，后续要用他来获取下一层的点
            }
        }
    }

    return d[n - 1][m - 1];
}
int main()
{
    memset(d, -1, sizeof d);//初始化
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> g[i][j];
        }
    }
    cout << dfs();
    return 0;
}