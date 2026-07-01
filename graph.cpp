#include<bits/stdc++.h>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<pair<int,int>>> adj;

public:
    Graph(int V){
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u,int v,int w){
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    void printGraph(){
        for(int i=0;i<V;i++){
            cout<<i<<" -> ";

            for(auto edge:adj[i]){
                cout<<edge.first<<"("<<edge.second<<") ";
            }
            cout<<endl;
        }
    }

    void printDFS(int node,vector<bool>& vis){
        vis[node]=true;
        cout<<node<<" ";

        for(auto adjNode:adj[node]){
            if(!vis[adjNode.first]){
                printDFS(adjNode.first,vis);
            }
        }
    }

    void printBFS(int node){
        vector<bool> vis(V,false);
        queue<int> q;

        vis[node]=true;
        q.push(node);

        while(!q.empty()){
            int front=q.front();
            q.pop();

            cout<<front<<" ";

            for(auto adjNode:adj[front]){
                if(!vis[adjNode.first]){
                    vis[adjNode.first]=true;
                    q.push(adjNode.first);
                }
            }
        }

        cout<<endl;
    }

    vector<int> dijkstra(int src){
        vector<int> dist(V,INT_MAX);
        dist[src]=0;
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

        pq.push({0,src});

        while(!pq.empty()){
            auto[cdist,node]=pq.top();
            pq.pop();
            if(cdist>dist[node]) continue;
            for(auto adjNode:adj[node]){
                auto[adjV,ndist]=adjNode;
                if(ndist+cdist<dist[adjV]){
                    dist[adjV]=ndist+cdist;
                    pq.push({dist[adjV],adjV});
                }
            }
        }
    return dist;
    }

    int dijkstra(int src,int dest){
        vector<int> dist(V,INT_MAX);
        dist[src]=0;
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        pq.push({0,src});

        while(!pq.empty()){
            auto[cdist,node]=pq.top();
            pq.pop();
            if(cdist>dist[node]) continue;
            if(node==dest) return cdist;
            for(auto adjNode:adj[node]){
                auto[adjV,ndist]=adjNode;
                if(ndist+cdist<dist[adjV]){
                    dist[adjV]=ndist+cdist;
                    pq.push({dist[adjV],adjV});
                }
            }
        }
    return dist[dest];
    }

    bool hasCycle(int parent,int node,vector<bool>& vis){
        vis[node]=true;
        for(auto adjNode:adj[node]){
            if(!vis[adjNode.first]){
                if(hasCycle(node,adjNode.first,vis)) return true;
            }else if(adjNode.first!=parent) return true;
        }
        return false;
    }

    bool isBipartite(vector<int>& color,int node){
        for(auto adjNode:adj[node]){
            if(color[adjNode.first]==-1){
                color[adjNode.first]=1-color[node];
                if(!isBipartite(color,adjNode.first)) return false;
            }else if(color[adjNode.first]==color[node]) return false;
        }
        return true;
    }

    // to store the the MST path, change pair->tuple in the pq, store the parent, and then print/ add to a vector
    int prims(int node,vector<bool>& vis){
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        pq.push({0,node});
        int res=0;
        while(!pq.empty()){
            auto[wt,newNode]=pq.top();
            pq.pop();
            if(vis[newNode]) continue;
            vis[newNode]=true;
            res+=wt;
            for(auto adjNode:adj[newNode]){
                auto[adjV,nwt]=adjNode;
                if(!vis[adjV]) pq.push({nwt,adjV});
            }
        }
        return res;
    }
    
};



int main(){
    Graph g(10);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);

    g.addEdge(1, 3, 2);
    g.addEdge(1, 4, 7);

    g.addEdge(2, 5, 4);
    g.addEdge(2, 6, 6);

    g.addEdge(3, 7, 5);

    g.addEdge(4, 7, 1);
    g.addEdge(4, 8, 8);

    g.addEdge(5, 8, 3);

    g.addEdge(6, 9, 2);

    g.addEdge(7, 9, 4);

    g.addEdge(8, 9, 1);

    cout<<"the graph is: "<<endl;
    g.printGraph();
    cout<<endl;

    cout<<"bfs: "<<endl;
    g.printBFS(0);
    cout<<endl;

    vector<bool> vis(10);

    cout<<"dfs: "<<endl;
    g.printDFS(0,vis);
    cout<<endl;

    cout<<"dijkstra (0 to all):\n";

    vector<int> dist = g.dijkstra(0);

    for(int i=0;i<dist.size();i++){
        cout<<"0 -> "<<i<<" = "<<dist[i]<<endl;
    }

    cout<<endl;

    cout<<"Shortest path from 0 to 9 = "<<g.dijkstra(0,9)<<endl;

    vector<bool> newVis(10,false);
    cout<<"has a cycle? ";
    if(g.hasCycle(-1,0,newVis)) cout<<"true"<<endl;
    else cout<<"false"<<endl;

    vector<int> color(10, -1);
    bool ans=true;
    for(int i=0;i<10;i++){
        if(color[i]==-1){
            color[i]=0;
            if(!g.isBipartite(color, i)){
                ans=false;
                break;
            }
        }
    }
    cout<<"Is Bipartite? ";
    if(ans) cout<<"true"<<endl;
    else cout<<"false"<<endl;

    vector<bool> primVis(10,false);
    int primsMST=g.prims(0,primVis);
    cout<<"Prim's MST weight is: "<<primsMST<<endl;

}