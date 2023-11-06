#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int N = 1e5 + 10;

int n, m;
int e[N], ne[N], h[N], w[N], idx;
int dist[N], cnt[N];//cnt[i]表示从1到i的边数, 点数 = 边数 + 1;
bool st[N];//st[i]用来标记i点是否进入了待更新的队列中

void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

bool spfa()
{
    //不用初始化dist数组，是因为只要有负环，就换一直“转”，让dist[i]趋近于-INF, 所以不管初始值为多少都不影响答案
    queue<int> q;
    //因为如果从1开始，可能走不到负环的位置，不一定1和负环的位置联通了
    for (int i = 1; i <= n; i++)
    {
        q.push(i);
        st[i] = true;
    }

    while (q.size())
    {
        int t = q.front();
        q.pop();

        st[t] = false;//出队

        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];

            //判断是正环还是负环
            if (dist[j] > dist[t] + w[i])//j是当前遍历到的点，t是正在用来更新其他点的 点 ， 
            {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[t] + 1;
                //从1到j有n条边那么，1到n之间就有 n + 1个点，但是只有n个点，所以只有可能是有个点被算了2次，就存在负环
                if (cnt[j] >= n) return true;

                if (!st[j])//被更新了，且没有用过就入队
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }

    return false;

}
int main()
{
    cin >> n >> m;


    memset(h, -1, sizeof h);

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    if (spfa()) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}