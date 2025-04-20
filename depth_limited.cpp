#include <bits/stdc++.h>
using namespace std;

vector<int> g[100010];

bool dls(int node, int target, int depth, unordered_set<int> &visited)
{
    if (depth < 0)
        return false;

    cout << node << " ";
    if (node == target)
        return true;

    visited.insert(node);

    for (int neighbor : g[node])
    {
        if (visited.find(neighbor) == visited.end())
        {
            if (dls(neighbor, target, depth - 1, visited))
                return true;
        }
    }

    return false;
}

int main()
{
    int v, e;
    cin >> v >> e;

    for (int i = 0; i < e; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int start, target, maxDepth;
    cin >> start >> target >> maxDepth;

    unordered_set<int> visited;

    if (dls(start, target, maxDepth, visited))
    {
        cout << "\nTarget found\n";
    }
    else
    {
        cout << "\nTarget not found within depth\n";
    }

    return 0;
}
