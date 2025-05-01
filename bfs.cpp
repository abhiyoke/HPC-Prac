#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

vector<vector<int>> g;
vector<bool> vis;
int n;
void pbfs(int s)
{
    queue<int> q;
    for (int i = 0; i < n; i++)
        vis[i] = false;
    q.push(s);
    vis[s] = true;

    while (!q.empty())
    {
        int s = q.size();

#pragma omp parallel for
        for (int i = 0; i < s; i++)
        {
            int u;
#pragma omp critical
            {
                u = q.front();
                q.pop();
            }
            cout << u << " ";
#pragma omp parallel for
            for (int j = 0; j < g[u].size(); j++)
            {
                if (!vis[g[u][j]])
                {
#pragma omp critical
                    {
                        if (!vis[g[u][j]])
                        {
                            vis[g[u][j]] = true;
                            q.push(g[u][j]);
                        }
                    }
                }
            }
        }
    }
}
int main()
{

    int e;
    cin >> n >> e;
    g.resize(n);
    vis.resize(n);
    for (int i = 0; i < e; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    double start_time = omp_get_wtime();
    pbfs(0);
    double end_time = omp_get_wtime();
    cout << endl;
    cout << "Time taken: " << end_time - start_time;
    return 0;
}