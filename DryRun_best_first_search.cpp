#include <bits/stdc++.h>
using namespace std;

vector<int> bestFirstSearch(vector<vector<int>> edges, int src, int target, int n)
{
    vector<vector<pair<int, int>>> adj(n);
    for (auto &edge : edges)
    {
        int u = edge[0], v = edge[1], w = edge[2];
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w); // undirected
    }

    cout << "\n=== Adjacency List ===" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << "Node " << i << " -> ";
        for (auto &p : adj[i])
        {
            cout << "(" << p.first << ", w:" << p.second << ") ";
        }
        cout << endl;
    }

    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, src});
    visited[src] = true;

    vector<int> path;
    int step = 1;

    cout << "\n=== Search Progress ===" << endl;

    while (!pq.empty())
    {
        cout << "\n--- Step " << step++ << " ---" << endl;

        pair<int, int> top = pq.top();
        int cost = top.first;
        int node = top.second;

        pq.pop();
        cout << "Processing node: " << node << " (cost: " << cost << ")" << endl;
        path.push_back(node);

        if (node == target)
        {
            cout << "Target node " << target << " found. Ending search." << endl;
            break;
        }

        cout << "Checking neighbors of node " << node << ":\n";
        for (auto &p : adj[node])
        {
            int neighbor = p.first;
            int weight = p.second;
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                pq.push({weight, neighbor});
                cout << "  Added node " << neighbor << " to queue with cost " << weight << endl;
            }
            else
            {
                cout << "  Node " << neighbor << " already visited, skipping." << endl;
            }
        }

        cout << "Current path: ";
        for (int x : path)
            cout << x << " ";
        cout << endl;
    }

    return path;
}

int main()
{
    int n, e;
    cout << "Enter number of nodes: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> e;

    vector<vector<int>> edgeList(e);
    cout << "Enter edges (format: u v w):\n";
    for (int i = 0; i < e; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edgeList[i] = {u, v, w};
    }

    int source, target;
    cout << "Enter source node: ";
    cin >> source;
    cout << "Enter target node: ";
    cin >> target;

    vector<int> path = bestFirstSearch(edgeList, source, target, n);

    cout << "\n=== Final Result ===" << endl;
    cout << "Path from " << source << " to " << target << ": ";
    for (int node : path)
        cout << node << " ";
    cout << endl;

    return 0;
}
