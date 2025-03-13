#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>

using namespace std;

vector<int> BFS(vector<vector<int>>&, vector<bool>&, int, int);
void DFSrec(vector<vector<int>>&, vector<bool>&, int);
void DFS(vector<vector<int>>&);
vector<int> DTopologicalSort(vector<vector<int>>&);
void TopologicalSortDFS(vector<vector<int>>&, stack<int>&, vector<bool>&, int);
vector<int> BFSTopologicalSort(vector<vector<int>>&);

int main(){
	
/*---------------------- Initialization ----------------------*/

	int V = 10;	//size (nodes)
	
	//Adjacency Matrix
	vector<vector<bool>> adj_matrix ( V, vector<bool>(V,0) );
	
	//Adjacency List
	vector<vector<int>> adj_list (V);
	
/*---------------------- Reading Graphs ----------------------*/

	int E = 5;	//number of edges
	
	//Adjacency Matrix
	for(int i=0; i<E; i++){
		
		int source, dest;
		cin >> source >> dest;
		
		source--;dest--;		//0-based
		
		adj_matrix[source][dest] = 1;
		adj_matrix[dest][source] = 1;		//undirected graph
		
	}
	
	//Adjacency List
	for(int i=0; i<E; i++){
		
		int source, dest;
		cin >> source >> dest;
		
		source--;dest--;		//0-based
		
		adj_list[source].push_back(dest);
		adj_list[dest].push_back(source);		//undirected graph
	}
	
/*---------------------- BFS Traversal ----------------------*/
	vector<bool>visited(V,false);
	
	vector<int> ans = BFS(adj_list, visited, V, 0);
	
	//to perform bfs on all the graph (handles disconnected graphs)
	for(int i=0; i<V; i++){
		vector<int> ans = BFS(adj_list, visited, V, i);
	}
	
/*---------------------- DFS Traversal ----------------------*/
	DFS(adj_list);
	
	return 0;
}

//																	  size   starting point
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
		
		for(auto &x: adj_list[curr]){
			if(!visited[x]){
				q.push(x);
				visited[x] = true;
			}
		}
		
	}
	
	return res;
}

/*---------------------- DFS Traversal ----------------------*/
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

/*---------------------- Topological Sort ----------------------*/
/*----------------------        DFS       ----------------------*/
vector<int> DTopologicalSort(vector<vector<int>>& adj_list){
	int V = adj_list.size();
	stack<int>topo_stack;
	vector<bool>visited(V,false);
	
	//loop through unvisited nodes and perform the topological traversing
	for(int i=0; i<V; i++){
		if(!visited[i]){
			TopologicalSortDFS(adj_list, topo_stack, visited, i);
		}
	}
	
	//pop the vertices from stack to vector to sort them
	vector<int>ans;
	while(!topo_stack.empty()){
		ans.push_back(topo_stack.top());
		topo_stack.pop();
	}
	
	return ans;
}
void TopologicalSortDFS(vector<vector<int>>& adj_list, stack<int>& topo_stack, vector<bool>& visited, int i){
	//append the vertices to stack after traversing all of its children
	visited[i] = true;
	
	for(auto &x: adj_list[i]){
		if(!visited[x]){
			TopologicalSortDFS(adj_list, topo_stack, visited, x);
		}
	}
	
	topo_stack.push(i);
}
/*----------------------    BFS (Kahn's)   ----------------------*/
vector<int> BFSTopologicalSort(vector<vector<int>>& adj_list){
	int V = adj_list.size();
	
	//calculate the in degree of all nodes
	vector<int>indegree(V,0);
	for(int i=0; i<V; i++){
		for(auto &x: adj_list[i]){
			indegree[x]++;
		}
	}
	
	//push vertex with 0 in degree to the queue
	queue<int>q;
	for(int i=0; i<V; i++){
		if(indegree[i] == 0){
			q.push(i);
		}
	}
	
	
	vector<int>ans;
	while(!q.empty()){
		int curr = q.front();
		q.pop();
		ans.push_back(curr);
		
		//traverse children of the 0 in degree node and
		//decrement in degree of all children
		for(auto &x: adj_list[curr]){
			indegree[x]--;
			
			//only push 0 in degree children
			if(indegree[x] == 0){
				q.push(x);
			}
		}
	}
	
	return ans;
}
