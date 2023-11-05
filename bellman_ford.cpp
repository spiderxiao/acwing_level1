#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int N = 510, M = 1e5 + 10;

int n, m, k;
int dist[N], last[N];

struct Edge
{
    int a, b, c;
}edges[M];


void bellman_ford()
{
    //初始化
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    //保证只操作k次
    for (int i = 0; i < k; i++)
    {
        //每次要用没更新的dist
        memcpy(last, dist, sizeof dist);

        for (int j = 0; j < m; j++)
        {
            auto e = edges[j];

            //这里用没更新的dist[e.a]来更新dist[e.b]是因为，如过dist[e.a]更新过，那么肯定小于
            //最先初始化的0x3f3f3f3f，那么也就意味着dist[e.b]也必会被更新，但是我们只能进行k次操作,
            //如果在在这里更新dist[e.b]用了更新了的dist[e.a]，那么意味着我在这次循环中用了两条边，相当于操作了两次
            //这样就不满足只操作k次的条件
            dist[e.b] = min(dist[e.b], last[e.a] + e.c);
        }
    }

}
int main()
{
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        edges[i] = { a, b, c };
    }

    bellman_ford();

    //这里的判断没有想上一题用dist[n] == 0x3f3f3f3f来判断，是因为上一题都是正权，假如1->2->3->4, 5->6
    //且5到6的权值为负数，因为上一题是正权，肯定不会让5->6这一路径的dist[6]更新，但是如果是负数
    //min函数就会调用，使得dist[6]变小，所以根据数据判断后最小不会小于0x3f3f3f3f / 2这个值，即证
    if (dist[n] > 0x3f3f3f3f / 2) cout << "impossible" << endl;
    else cout << dist[n] << endl;
    return 0;
}