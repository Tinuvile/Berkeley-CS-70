#include <iostream>  
#include <vector>  
#include <stack>  
#include <algorithm>  
#include <list>  
using namespace std;

class Graph {
public:
    int V;  // Number of vertices  
    vector<list<int>> adj;  // Adjacency list  

    // Constructor to initialize the graph with V vertices  
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // Function to add an undirected edge between u and v  
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Function to find a tour starting from vertex s  
    list<int> findTour(int s);

    // Function to splice multiple tours into one  
    list<int> splice(list<int>& T, vector<list<int>>& tours);

    // Recursive function to find an Eulerian tour  
    list<int> Euler(int s);
};

list<int> Graph::findTour(int s) {
    list<int> tour;
    stack<int> stk;
    vector<bool> visitedEdges(V, false);
    stk.push(s);

    while (!stk.empty()) {
        int currentVertex = stk.top();
        if (!adj[currentVertex].empty()) {
            int nextVertex = adj[currentVertex].front();
            adj[currentVertex].pop_front();
            adj[nextVertex].remove(currentVertex);
            stk.push(nextVertex);
        }
        else {
            tour.push_front(currentVertex);
            stk.pop();
        }
    }
    return tour;
}

list<int> Graph::splice(list<int>& T, vector<list<int>>& tours) {
    list<int> result = T;
    for (auto& subTour : tours) {
        auto it = find(result.begin(), result.end(), subTour.front());
        result.splice(it, subTour);
    }
    return result;
}

list<int> Graph::Euler(int s) {
    list<int> T = findTour(s);
    vector<list<int>> subTours;

    for (auto it = T.begin(); it != T.end(); ++it) {
        int vertex = *it;
        if (!adj[vertex].empty()) {
            Graph subGraph(V);
            subGraph.adj = adj;
            list<int> subTour = subGraph.Euler(vertex);
            subTours.push_back(subTour);
        }
    }
    return splice(T, subTours);
}

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);
    g.addEdge(1, 3);

    list<int> eulerianTour = g.Euler(0);

    cout << "Eulerian Tour: ";
    for (int vertex : eulerianTour) {
        cout << vertex << " ";
    }
    cout << endl;

    return 0;
}