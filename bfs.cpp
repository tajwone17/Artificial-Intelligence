#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

void bfs(int start, vector<vector<int>> &graph)
{
    unordered_set<int> visited;
    queue<int> queue;

    queue.push(start);
    visited.insert(start);

    while (!queue.empty())
    {
        int vertex = queue.front();
        queue.pop();

        cout << vertex << " ";

        for (int neighbor : graph[vertex])
        {
            if (visited.find(neighbor) == visited.end())
            {
                queue.push(neighbor);
                visited.insert(neighbor);
            }
        }
    }
}

int main()
{
    int numVertices, numEdges, startVertex;

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

    bfs(startVertex, graph);

    return 0;
}