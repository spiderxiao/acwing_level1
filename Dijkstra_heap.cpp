#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

const int N = 1e6 + 10;

int n, m;
int dist[N];
int h[N], ne[N], e[N], w[N], idx;
bool st[N];
void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

//用堆排序是优化了每一次找最短路径的、没被用过的点
int dijkstra()
{
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({ 0, 1 });//先插入第一个点，每个节点的第一个值是路径距离，第二个值是编号
    dist[1] = 0;//初始化第一个点的距离

    while (heap.size())
    {

        auto t = heap.top();
        heap.pop();//这里虽然弹出了这个最小点，但是为了防止这个点被再次加入堆中，所以需要st数组来标记

        int ver = t.second;

        if (st[ver]) continue;
        else
        {
            st[ver] = true;

            //更新路径
            for (int i = h[ver]; i != -1; i = ne[i])
            {
                int j = e[i];
                if (dist[j] > dist[ver] + w[i])
                {
                    dist[j] = dist[ver] + w[i];
                    //只要这个点被更新了，那么后续点由这个点得到的路径都需要更新，所以要把这个点加入堆
                    heap.push({ dist[j], j });
                }
            }
        }

    }

    if (dist[n] == 0x3f3f3f3f) return -1;
    else return dist[n];

}
int main()
{
    memset(h, -1, sizeof h);
    memset(dist, 0x3f, sizeof dist);

    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }

    cout << dijkstra() << endl;

    return 0;
}