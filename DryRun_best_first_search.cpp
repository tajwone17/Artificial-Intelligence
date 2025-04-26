#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
#include <algorithm>

using namespace std;

pair<bool, vector<int>> bestFirstSearch(
    int start,
    int target,
    vector<vector<int>> &graph,
    const function<double(int, int)> &heuristic)
{
    unordered_map<int, double> cost;
    unordered_map<int, int> parent;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> queue;

    cost[start] = 0;
    queue.push({heuristic(start, target), start});

    cout << "\n====== Starting Best First Search ======\n";

    while (!queue.empty())
    {
        // Show queue status
        cout << "\nPriority Queue: [ ";
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> tempQueue = queue;
        while (!tempQueue.empty())
        {
            cout << "(" << tempQueue.top().second << ", priority=" << tempQueue.top().first << ") ";
            tempQueue.pop();
        }
        cout << "]\n";

        int current = queue.top().second;
        double currentPriority = queue.top().first;
        queue.pop();

        cout << "\nVisiting Node: " << current << " (Priority: " << currentPriority << ")\n";

        if (current == target)
        {
            cout << "Target node found!\n";
            vector<int> path;
            while (current != start)
            {
                path.push_back(current);
                current = parent[current];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());

            cout << "\nPath reconstruction:\n";
            for (int p : path)
                cout << p << " ";
            cout << endl;
            return {true, path};
        }

        for (int neighbor : graph[current])
        {
            double newCost = cost[current] + 1;
            cout << "  Considering neighbor: " << neighbor << " (New Cost: " << newCost << ")";

            if (cost.find(neighbor) == cost.end() || newCost < cost[neighbor])
            {
                cost[neighbor] = newCost;
                parent[neighbor] = current;
                double priority = heuristic(neighbor, target) + newCost;
                queue.push({priority, neighbor});
                cout << " -> Added to queue with priority " << priority;
            }
            cout << endl;
        }

        // Show cost and parent maps
        cout << "Cost Map: ";
        for (auto &kv : cost)
            cout << "[" << kv.first << ":" << kv.second << "] ";
        cout << "\nParent Map: ";
        for (auto &kv : parent)
            cout << "[" << kv.first << "<-" << kv.second << "] ";
        cout << endl;
    }

    cout << "\nTarget node not reachable from start.\n";
    return {false, {}};
}

int main()
{
    int numVertices = 5, numEdges = 6;
    vector<vector<int>> graph(numVertices);

    vector<pair<int, int>> edges = {
        {0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}, {1, 4}
    };

    for (auto &edge : edges)
    {
        graph[edge.first].push_back(edge.second);
        graph[edge.second].push_back(edge.first);
    }

    int startVertex = 0;
    int targetVertex = 4;

    // Use a lambda heuristic compatible with C++17
    auto heuristic = [](int a, int b) -> double {
        return 1.0; // uniform cost
    };

    auto result = bestFirstSearch(startVertex, targetVertex, graph, heuristic);

    if (!result.first)
    {
        cout << "\nTarget vertex not found.\n";
    }

    return 0;
}
