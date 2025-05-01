#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

vector<vector<int>> g;
vector<bool> vis;
int n;
void pdfs(int s)
{
    stack<int> st;
    for (int i = 0; i < n; i++)
        vis[i] = false;
    st.push(s);
#pragma omp parallel
    {
        while (1)
        {
            int u = -1;
#pragma omp critical
            if (!st.empty())
            {
                u = st.top();
                st.pop();
            }
            if (u == -1)
                break;

            if (!vis[u])
            {
#pragma omp critical
                {
                    if (!vis[u])
                    {
                        vis[u] = true;
                        cout << u << " ";
                    }
                }
                vector<int> ne;
#pragma omp critical
                {
                    ne = g[u];
                }
#pragma omp critical
                {
                    for (int i = ne.size() - 1; i >= 0; i--)
                    {
                        if (!vis[ne[i]])
                            st.push(ne[i]);
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
    pdfs(0);
    double end_time = omp_get_wtime();
    cout << endl;
    cout << "Time taken: " << end_time - start_time;
    return 0;
}