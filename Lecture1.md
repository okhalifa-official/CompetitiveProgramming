# Introduction to Graphs

## Overview
This lecture covers fundamental concepts in graph theory, including different ways to represent graphs in memory and essential algorithms for traversing graphs. Understanding these concepts is crucial for solving complex problems in computer science, including pathfinding, network analysis, and many algorithmic challenges.

## Graph Representation

Graphs can be represented in computer memory using two primary methods, each with distinct advantages and use cases.

### 1. Adjacency Matrix

An adjacency matrix is a 2D array representation of a graph where each cell `adj_matrix[i][j]` indicates whether there's an edge between vertex `i` and vertex `j`.

**Key Characteristics:**
- **Space Complexity:** O(V²) where V is the number of vertices
- **Time Complexity:** O(1) for checking if an edge exists between two vertices
- **Best For:** Dense graphs (graphs with many edges)
- **Memory Usage:** Fixed size regardless of actual number of edges
- **Undirected Graphs:** The matrix is symmetric (`adj_matrix[i][j] = adj_matrix[j][i]`)

**Advantages:**
- Fast edge lookup
- Simple implementation
- Easy to work with for mathematical operations

**Disadvantages:**
- Memory inefficient for sparse graphs
- Adding/removing vertices requires resizing the entire matrix

```cpp
#include <vector>
int V = 10; // Number of Nodes
int E = 5;  // Number of edges
vector<vector<bool>>adj_matrix(V, vector<V,false>);

for(int i=0; i<E; i++){
    int src, dst;
    cin >> src >> dst;
    adj_matrix[src][dst] = 1;   // Edge between src and dst
    adj_matrix[dst][src] = 1;   // If undirectected
}

```
### 2. Adjacency List

An adjacency list represents a graph as an array of lists, where each list contains the neighbors of a vertex.

**Key Characteristics:**
- **Space Complexity:** O(V + E) where V is vertices and E is edges
- **Time Complexity:** O(degree of vertex) to find all neighbors of a vertex
- **Best For:** Sparse graphs (graphs with fewer edges)
- **Memory Usage:** Only stores actual edges, not empty connections
- **Dynamic:** Easy to add/remove edges and vertices

**Advantages:**
- Memory efficient for sparse graphs
- Fast iteration over neighbors
- Dynamic size adjustment

**Disadvantages:**
- Slower edge lookup compared to matrix
- More complex for some mathematical operations

```cpp
#include <vector>
int V = 10; // Number of Nodes
int E = 5;  // Number of edges
vector<vector<int>>adj_list(V);

for(int i=0; i<E; i++){
    int src, dst;
    cin >> src >> dst;
    adj_list[src].push_back(dst);   // Edge between src and dst
    adj_list[dst].push_back(src);   // If undirectected
}

```

## Traversal

Graph traversal algorithms are fundamental techniques for exploring all vertices and edges in a graph. The two primary methods are Breadth-First Search (BFS) and Depth-First Search (DFS).

### 1. BFS (Breadth-First Search)

BFS explores the graph level by level, visiting all vertices at distance 1 from the source, then distance 2, and so on.

**Algorithm Characteristics:**
- **Data Structure:** Uses a queue (FIFO - First In, First Out)
- **Time Complexity:** O(V + E)
- **Space Complexity:** O(V) for the visited array and queue
- **Traversal Pattern:** Level-order traversal
- **Guarantee:** Finds shortest path in unweighted graphs

**Applications:**
- Finding shortest path in unweighted graphs
- Level-order tree traversal
- Connected components detection
- Social network analysis (degrees of separation)
- Web crawling

**Key Steps:**
1. Start from source vertex, mark as visited
2. Add source to queue
3. While queue is not empty:
   - Dequeue a vertex and process it
   - Examine all unvisited neighbors
   - Mark neighbors as visited and enqueue them

```cpp
vector<int> BFS(vector<vector<int>>& adj_list, vector<bool>& visited, int V, int S){
	
	vector<int>res;		//result (output)
	
	queue<int>q;
	
	visited[S] = true;
	q.push(S);
	
	//iterate over the queue
	while(!q.empty()){
		
		int curr = q.front();
		q.pop();
		res.push_back(curr);
		
        // iterate over all neighbbors
        // visit all unvisited neighbors
        // push neighbor to the queue
		for(auto &x: adj_list[curr]){
			if(!visited[x]){
				q.push(x);
				visited[x] = true;
			}
		}
		
	}
	return res;
}

int main(){
    ..
    ..
    vector<bool>visited(V,false);
	
    vector<int> ans = BFS(adj_list, visited, V, 0);
	
    //to perform bfs on all the graph (handles disconnected graphs)
    for(int i=0; i<V; i++){
    	vector<int> ans = BFS(adj_list, visited, V, i);
    }
}
    
```
### 2. DFS (Depth-First Search)

DFS explores the graph by going as deep as possible along each branch before backtracking.

**Algorithm Characteristics:**
- **Data Structure:** Uses recursion (implicit stack) or explicit stack
- **Time Complexity:** O(V + E)
- **Space Complexity:** O(V) for the visited array and recursion stack
- **Traversal Pattern:** Goes deep first, then backtracks
- **Memory:** Stack depth can be as large as the longest path

**Applications:**
- Topological sorting
- Cycle detection in graphs
- Connected components detection
- Maze solving
- Finding strongly connected components
- Backtracking algorithms

**Key Steps:**
1. Start from a vertex, mark as visited
2. Process the current vertex
3. Recursively visit all unvisited neighbors
4. Backtrack when no more unvisited neighbors exist
5. The outer loop handles disconnected components

**Important Implementation Details:**

**Handling Disconnected Graphs:**
Both algorithms include mechanisms to handle disconnected graphs by ensuring all vertices are visited even if they're not reachable from the starting vertex.

**Visited Array:**
A boolean array tracks visited vertices to prevent infinite loops and ensure each vertex is processed exactly once.

```cpp
void DFS(vector<vector<int>>& adj_list){
	//this function sets the visited list and calls the recursion
	
	int V = adj_list.size();
	vector<bool>visited(V,false);
	
	//for loop to handle disconnected graphs
	for(int i=0; i<V; i++){
		if(!visited[i]){
			DFSrec(adj_list, visited, i);
		}
	}
}

void DFSrec(vector<vector<int>>& adj_list, vector<bool>& visited, int s){
	//visit current vertex
	visited[s] = true;
	
	//print current vertex
	cout << s << " ";
	
	//loop through edges, if not visited then go visit
	for(auto &x: adj_list[s]){
		if(!visited[x]){
			DFSrec(adj_list, visited, x);
		}
	}
}

int main(){
    ..
    DFS(adj_list);
}
```

## Summary of Key Concepts

### **Graph Representation Comparison**

| Aspect | Adjacency Matrix | Adjacency List |
|--------|-----------------|----------------|
| **Space Complexity** | O(V²) | O(V + E) |
| **Edge Lookup Time** | O(1) | O(degree of vertex) |
| **Best Use Case** | Dense graphs | Sparse graphs |
| **Memory Efficiency** | Fixed size, can waste space | Dynamic, only stores actual edges |
| **Implementation** | 2D boolean array | Vector of vectors |

### **Graph Traversal Comparison**

| Aspect | BFS | DFS |
|--------|-----|-----|
| **Data Structure** | Queue (FIFO) | Stack/Recursion (LIFO) |
| **Traversal Pattern** | Level by level | Deep first, then backtrack |
| **Path Guarantee** | Shortest path in unweighted graphs | May not find shortest path |
| **Memory Usage** | Queue + visited array | Recursion stack + visited array |
| **Applications** | Shortest path, level traversal | Cycle detection, topological sort |

### **Common Implementation Patterns**

**Disconnected Graph Handling:**
Both BFS and DFS require loops to ensure all vertices are visited:
- **BFS:** Loop through all vertices and call BFS on unvisited ones
- **DFS:** Main function loops and calls recursive DFS on unvisited vertices

**Visited Array Management:**
- Initialize boolean array to `false` for all vertices
- Mark vertex as visited **before** adding to queue (BFS) or processing (DFS)
- Prevents infinite loops and ensures O(V + E) time complexity

**Edge Cases to Consider:**
- Empty graphs (no vertices or edges)
- Single vertex graphs
- Disconnected components
- Self-loops (edges from vertex to itself)
- Parallel edges (multiple edges between same vertices)

These fundamental concepts form the foundation for more advanced graph algorithms including shortest path algorithms (Dijkstra's, Bellman-Ford), minimum spanning trees (Kruskal's, Prim's), and network flow algorithms.