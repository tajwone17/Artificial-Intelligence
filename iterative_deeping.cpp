#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

// Function to perform DFS with a given maximum depth
bool dfs(int start, int target, vector<vector<int>> &graph, int depth, unordered_set<int> &visited)
{
    if (depth == 0 && start == target)
    {
        return true;
    }

    if (depth == 0)
    {
        return false;
    }

    visited.insert(start);

    for (int neighbor : graph[start])
    {
        if (visited.find(neighbor) == visited.end())
        {
            if (dfs(neighbor, target, graph, depth - 1, visited))
            {
                return true;
            }
        }
    }

    return false;
}

bool iddfs(int start, int target, vector<vector<int>> &graph, int maxDepth)
{
    for (int depth = 0; depth <= maxDepth; depth++)
    {
        unordered_set<int> visited;
        if (dfs(start, target, graph, depth, visited))
        {
            return true;
        }
    }

    return false;
}

int main()
{
    int numVertices, numEdges, startVertex, targetVertex, maxDepth;

    cout << "Enter the number of vertices: ";
    cin >> numVertices;

    vector<vector<int>> graph(numVertices);

    cout << "Enter the number of edges: ";
    cin >> numEdges;

    cout << "Enter the edges (vertex1 vertex2):\n";
    for (int i = 0; i < numEdges; i++)
    {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;
        graph[vertex1].push_back(vertex2);
        graph[vertex2].push_back(vertex1);
    }

    cout << "Enter the starting vertex: ";
    cin >> startVertex;

    cout << "Enter the target vertex: ";
    cin >> targetVertex;

    cout << "Enter the maximum depth: ";
    cin >> maxDepth;

    if (iddfs(startVertex, targetVertex, graph, maxDepth))
    {
        cout << "Target vertex found within the maximum depth." << endl;
    }
    else
    {
        cout << "Target vertex not found within the maximum depth." << endl;
    }

    return 0;
}