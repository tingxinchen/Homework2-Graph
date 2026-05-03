//41343128
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <queue>

using namespace std;

struct Edge {
    int u, v;
};

class Graph {
private:
    int n;
    int num;
    vector<int>* adj;

public:
    Graph(int nodes) : n(nodes) {
        adj = new vector<int>[n];
    }

    ~Graph() {
        delete[] adj;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);

    }

    void showMartix() {
        vector<int>::iterator it;
        cout << "  ";
        for (int k = 0; k < n; k++) {
            cout << k << " ";
        }
        cout << endl;
        for (int i = 0; i < n; ++i) {
            cout << i << " ";
            it = adj[i].begin();
            for (int j = 0; j < n; j++) {
                if (find(adj[i].begin(), adj[i].end(), j) != adj[i].end()) {
                    cout << "1 ";
                    ++it;
                }
                else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }

    void showArraylist() {
        vector<int>::iterator it;
        for (int i = 0; i < n; ++i) {
            cout << i << " : ";
            for (it = adj[i].begin(); it < adj[i].end(); ++it)
                cout << *it << " ";
            cout << endl;
        }
    }
    void DFS_util(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        for (int w : adj[v]) {
            if (!visited[w]) {
                DFS_util(w, visited);
            }
        }
    }
    void DFS(int start) {
        vector<bool> visited(n, false);
        DFS_util(start, visited);
        cout << endl;
    }
    void BFS(int start) {

        vector<bool> visited(n, false);
        queue<int> q;

        //處理起點
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            //目前要的點
            int v = q.front();
            q.pop();
            cout << v << " ";

            //檢查
            for (int w : adj[v]) {
                if (!visited[w]) {
                    visited[w] = true; 
                    q.push(w);        
                }
            }
        }
        cout << endl;
    }
};



int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);

    g.showArraylist();
    g.showMartix();
    cout << endl;

    cout << "DFS:";
    g.DFS(0);
    cout << "BFS:";
    g.BFS(0);
    return 0;
}
