#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int N = 1e5 + 10;

int n, m;
int e[N], ne[N], h[N], w[N], idx;
int dist[N];
bool st[N];//st[i]用来标记i点是否进入了待更新的队列中

void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void spfa()
{
    dist[1] = 0;
    queue<int> q;
    q.push(1);
    st[1] = true;

    while (q.size())
    {
        int t = q.front();
        q.pop();

        st[t] = false;//出队

        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t] + w[i])//j是当前遍历到的点，t是正在用来更新其他点的 点 ， 
            {
                dist[j] = dist[t] + w[i];
                if (!st[j])//被更新了，且没有用过就入队
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
    //这里和bellman_ford算法的判断不同，因为bellman_ford算法是遍历所有边，没有被更新的点也有可能用来更新其他点
    //但是spfa算法只有被更新过的点才能用来更新其他点
    if (dist[n] == 0x3f3f3f3f) cout << "impossible" << endl;

    else cout << dist[n] << endl;

}
int main()
{
    cin >> n >> m;

    memset(dist, 0x3f, sizeof dist);
    memset(h, -1, sizeof h);

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }
    spfa();

    return 0;
}