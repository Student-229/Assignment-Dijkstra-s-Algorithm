#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm> 

using namespace std;

// Structure to represent an edge in the graph
struct Connection {
    string target;
    int cost;
};

// Function to execute Dijkstra’s Algorithm
void findShortestPath(unordered_map<string, vector<Connection>>& network, const string& source, const string& destination) {
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> minHeap;
    unordered_map<string, int> shortestDistance;
    unordered_map<string, string> previousNode;

    // Initialize all distances to infinity
    for (const auto& node : network) {
        shortestDistance[node.first] = numeric_limits<int>::max();
    }

    // Start node distance set to zero
    shortestDistance[source] = 0;
    minHeap.push({0, source});

    while (!minHeap.empty()) {
        string currentNode = minHeap.top().second;
        int currentCost = minHeap.top().first;
        minHeap.pop();

        if (currentNode == destination) break;

        for (const auto& link : network[currentNode]) {
            string neighbor = link.target;
            int newCost = currentCost + link.cost;

            if (newCost < shortestDistance[neighbor]) {
                shortestDistance[neighbor] = newCost;
                previousNode[neighbor] = currentNode;
                minHeap.push({newCost, neighbor});
            }
        }
    }

    // If no valid path exists
    if (shortestDistance[destination] == numeric_limits<int>::max()) {
        cout << "No route found from " << source << " to " << destination << endl;
        return;
    }

    cout << "Minimum cost from " << source << " to " << destination << ": " << shortestDistance[destination] << endl;

    // Construct and display the shortest path
    vector<string> path;
    for (string node = destination; node != ""; node = previousNode[node]) {
        path.push_back(node);
    }
    reverse(path.begin(), path.end());

    cout << "Optimal route: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << endl;
}

// Main function to accept user input and execute the algorithm
int main() {
    unordered_map<string, vector<Connection>> network;
    int totalEdges;

    cout << "Enter the number of edges: ";
    cin >> totalEdges;

    cout << "Provide edges in format (source destination weight):" << endl;
    for (int i = 0; i < totalEdges; i++) {
        string nodeA, nodeB;
        int linkWeight;
        cin >> nodeA >> nodeB >> linkWeight;

        // Only consider edges with positive weight
        if (linkWeight > 0) {
            network[nodeA].push_back({nodeB, linkWeight});
            network[nodeB].push_back({nodeA, linkWeight}); // Remove this for directed graphs
        }
    }

    string startNode, endNode;
    cout << "Enter the starting point: ";
    cin >> startNode;
    cout << "Enter the destination point: ";
    cin >> endNode;

    findShortestPath(network, startNode, endNode);

    return 0;
}
