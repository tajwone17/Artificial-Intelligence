#include<bits/stdc++.h>

using namespace std;

// Function to perform Best-First Search
// Returns a pair: a boolean indicating if the target was found, and the path to the target
pair<bool, vector<int>> bestFirstSearch(int start, int target, vector<vector<int>> &graph,
                                        function<double(int, int)> heuristic)
{
    unordered_map<int, double> cost; // Stores the cost to reach each node
    unordered_map<int, int> parent; // Stores the parent of each node for path reconstruction
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> queue; // Min-heap priority queue

    cost[start] = 0; // Cost to reach the start node is 0
    queue.push({heuristic(start, target), start}); // Push the start node with its heuristic value

    while (!queue.empty())
    {
        int current = queue.top().second; // Get the node with the lowest heuristic value
        queue.pop();

        // If the target node is found, reconstruct the path
        if (current == target)
        {
            vector<int> path;
            while (current != start)
            {
                path.push_back(current);
                current = parent[current]; // Move to the parent node
            }
            path.push_back(start); // Add the start node to the path
            reverse(path.begin(), path.end()); // Reverse the path to get the correct order
            return make_pair(true, path); // Return success and the path
        }

        // Explore all neighbors of the current node
        for (int neighbor : graph[current])
        {
            double newCost = cost[current] + 1; // Calculate the cost to reach the neighbor

            // If the neighbor is not visited or a cheaper path is found
            if (cost.find(neighbor) == cost.end() || newCost < cost[neighbor])
            {
                cost[neighbor] = newCost; // Update the cost to reach the neighbor
                parent[neighbor] = current; // Set the current node as the parent of the neighbor
                queue.push({heuristic(neighbor, target) + newCost, neighbor}); // Push the neighbor to the queue
            }
        }
    }

    return make_pair(false, vector<int>()); // Return failure if the target is not found
}

int main()
{
    int numVertices, numEdges, startVertex, targetVertex;

    // Input the number of vertices in the graph
    cout << "Enter the number of vertices: ";
    cin >> numVertices;

    vector<vector<int>> graph(numVertices); // Adjacency list representation of the graph

    // Input the number of edges in the graph
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    // Input the edges of the graph
    cout << "Enter the edges (vertex1 vertex2):\n";
    for (int i = 0; i < numEdges; i++)
    {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;
        graph[vertex1].push_back(vertex2); // Add edge from vertex1 to vertex2
        graph[vertex2].push_back(vertex1); // Add edge from vertex2 to vertex1 (undirected graph)
    }

    // Input the starting vertex
    cout << "Enter the starting vertex: ";
    cin >> startVertex;

    // Input the target vertex
    cout << "Enter the target vertex: ";
    cin >> targetVertex;

    // Define a simple heuristic function (constant value for demonstration)
    function<double(int, int)> heuristic = [](int a, int b)
    {
        return 1; // Constant heuristic value
    };

    // Perform Best-First Search
    pair<bool, vector<int>> result = bestFirstSearch(startVertex, targetVertex, graph, heuristic);

    // Output the result
    if (result.first)
    {
        cout << "Target vertex found. Path: ";
        for (int vertex : result.second)
        {
            cout << vertex << " "; // Print the path to the target
        }
        cout << endl;
    }
    else
    {
        cout << "Target vertex not found." << endl; // Target not found
    }

    return 0;
}