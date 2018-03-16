#include <bits/stdc++.h>
using namespace std;

class Graph
{
    int V;		    // No. of vertices
    list<int> *adj; // Pointer to an array containing adjacency lists
    int *nodesInComponent;
public:
	//Basic graph functions
    Graph(int V){
    	this->V = V;
    	adj = new list<int>[V];
    	nodesInComponent = new int[V];
    	for(int v = 0; v < V; ++v) nodesInComponent[v] = 0;	
    };   // Constructor

    void addEdge(int v, int w){
    	//add to list of v and list of w
    	adj[v].push_back(w);
    	adj[w].push_back(v);
    };

    //function to print count of components in the graph
    void connectedComponents(){
	    // Mark all the vertices as not visited
	    bool *visited = new bool[V];
	    for(int v = 0; v < V; v++) visited[v] = false;

		int count = 0;
		
	    for (auto v=0; v<V; v++){
	        if (visited[v] == false){
	        	int c = 0;		            	            
	            nodesInComponent[v] = DFS(v,visited,c);
	 			count++;
	        }
	    }
	    cout<<count<<" ";
	    //cout<<endl;
	    setNodesInComponent();
	    //for(int i = 0; i < V; ++i){ cout<<nodesInComponent[i]<<" ";}
	    
	}

	void setNodesInComponent(){			
		for(int i = 0; i < V; ++i){
			if(nodesInComponent[i] != 0){
				setValue(i,nodesInComponent ,nodesInComponent[i]);
			}
		}
	}

	void setValue(int v, int nodesInComponent[], int x){
		nodesInComponent[v] = x;
		for(auto u = adj[v].begin(); u!=adj[v].end(); ++u){
			if(nodesInComponent[*u] == 0){
				setValue(*u, nodesInComponent, nodesInComponent[v]);
			}
		}		
	}

	int DFS(int v, bool visited[], int &c){
		visited[v] = true;
		++c;
		for(auto u = adj[v].begin(); u!=adj[v].end(); ++u){
			if(visited[*u] == false){
				DFS(*u, visited, c);
			}
		}
		return c;
	}

	int findBiggestIslandEntrance(){
		auto max_size = max_element(nodesInComponent, nodesInComponent + V);
		auto it = find(nodesInComponent, nodesInComponent+V, *max_size);
		//cout<<"index "<< it - nodesInComponent<<endl; 
		return (it-nodesInComponent);
	}

	//function to print start time and finish time in smallest city
	void visitSmallestIsland(int entrance);

	//function to check cycle in graph
	void checkCycle(){
	    // Mark all the vertices as not visited and not part of recursion
	    // stack
	    bool *visited = new bool[V];
	    for (int i = 0; i < V; i++) visited[i] = false;
	 
	    // Call the recursive helper function to detect cycle in different DFS trees
	    for (int u = 0; u < V; u++)
	        if (!visited[u]) // Don't recur for u if it is already visited
	          if (isCyclicUtil(u, visited, -1)){
	          	 cout<<"YES\n";
	             return ;
	          }
	 	cout<<"NO\n";
	    return ;
	}


	// A recursive function that uses visited[] and parent to detect
	// cycle in subgraph reachable from vertex v.
	bool isCyclicUtil(int v, bool visited[], int parent)
	{
	    // Mark the current node as visited
	    visited[v] = true;
	 
	    // Recur for all the vertices adjacent to this vertex
	    list<int>::iterator i;
	    for (i = adj[v].begin(); i != adj[v].end(); ++i)
	    {
	        // If an adjacent is not visited, then recur for that adjacent
	        if (!visited[*i])
	        {
	           if (isCyclicUtil(*i, visited, v))
	              return true;
	        }
	 
	        // If an adjacent is visited and not parent of current vertex,
	        // then there is a cycle.
	        else if (*i != parent)
	           return true;
	    }
	    return false;
	}


	//visit neighbouring cities with distance at most k
	void visitBiggestIsland(int k){
		int count = 0 ;
		int entrance = findBiggestIslandEntrance();
		neighbouringCity(entrance, k);
	}

	//print list of start time and end time within distance k
	void neighbouringCity(int entrance, int k ){
		int u;
	   // Mark all the vertices as not visited
	    bool *visited = new bool[V];
	    for(int i = 0; i < V; i++) visited[i] = false;
	 
	    // Create a queue for BFS
	    queue<int> q;
	    //vector<int> k_nearest;	    
		int level[V];
		for(int i = 0; i < V; ++i){ level[i] = 0; }

	    visited[entrance] = true; // Mark the current node as visited and enqueue it
		level[entrance] = 0;
	    q.push(entrance);
   			    	   
	    //cout<<"\nstart BFS\n";   	    
		while(!q.empty() ){
			u = q.front();			
			//cout<<u+1<<" ";
			q.pop();

			//k_nearest.push_back(u);		
		
			for(auto i = adj[u].begin(); i!=adj[u].end(); ++i){
				if(visited[*i] == false){
					visited[*i] = true;
					level[*i] = level[u] + 1;
					q.push(*i);
				}
			}
		}
		
		//cout<<"\nprint level\n";
		for(int i = 0; i < V; ++i){
			if(level[i] <= k && level[i]!= 0) cout<<i+1<<" ";
			//cout<<level[i]<<" ";
		}

	}
};

int main(int argc, char const *argv[])
{
	int n,m,x,y,k;
	
	cin>>n>>m>>k;
	Graph g(n);

	for (int i = 0; i < m; ++i){
		cin>>x>>y;
		g.addEdge(x-1,y-1);
	}
	
	g.connectedComponents();
	g.checkCycle();
	//cout<<g.findBiggestIslandEntrance();
	g.visitBiggestIsland(k);
	return 0;
}