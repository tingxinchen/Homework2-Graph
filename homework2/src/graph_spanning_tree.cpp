#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Edge {
    int u, v;
    int weight;
};

bool cmp(Edge a, Edge b) {
    return a.weight < b.weight;
}

class Graph {
private:
    int n;

    vector<int> adj[100];      // 鄰居
    vector<int> weight[100];   // 權重

public:
    Graph(int nodes) {
        n = nodes;
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back(v);
        weight[u].push_back(w);

        adj[v].push_back(u);
        weight[v].push_back(w);
    }
    void showMatrix() {
        cout << "  ";
        for (int i = 0; i < n; i++) {
            cout << i << " ";
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            cout << i << " ";
            for (int j = 0; j < n; j++) {
                bool found = false;
                vector<int>::iterator it1 = adj[i].begin();
                vector<int>::iterator it2 = weight[i].begin();
                while (it1 != adj[i].end()) {
                    if (*it1 == j) {
                        cout << *it2 << " ";  
                        found = true;
                        break;
                    }
                    ++it1;
                    ++it2;
                }
                if (!found) {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }
    void showList() {
        vector<int>::iterator it1;
        vector<int>::iterator it2;

        for (int i = 0; i < n; i++) {
            cout << i << " : ";

            it1 = adj[i].begin();
            it2 = weight[i].begin();

            while (it1 != adj[i].end()) {
                cout << *it1 << "(w:" << *it2 << ") ";
                ++it1;
                ++it2;
            }
            cout << endl;
        }
    }

    void DFS_util(int v, bool visited[]) {
        visited[v] = true;
        cout << v << " ";

        vector<int>::iterator it;
        for (it = adj[v].begin(); it != adj[v].end(); ++it) {
            int next = *it;
            if (!visited[next]) {
                DFS_util(next, visited);
            }
        }
    }

    void DFS(int start) {
        bool visited[100] = { false };
        DFS_util(start, visited);
        cout << endl;
    }

    void BFS(int start) {
        bool visited[100] = { false };
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            vector<int>::iterator it;
            for (it = adj[v].begin(); it != adj[v].end(); ++it) {
                int next = *it;
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
        cout << endl;
    }

    int findParent(int x, int parent[]) {
        if (parent[x] == x)
            return x;
        return findParent(parent[x], parent);
    }

    void unite(int a, int b, int parent[]) {
        int rootA = findParent(a, parent);
        int rootB = findParent(b, parent);
        if (rootA != rootB)
            parent[rootA] = rootB;
    }

    void Kruskal() {
        vector<Edge> edges;

        // 收集邊
        for (int i = 0; i < n; i++) {
            vector<int>::iterator it1 = adj[i].begin();
            vector<int>::iterator it2 = weight[i].begin();

            while (it1 != adj[i].end()) {
                int v = *it1;
                int w = *it2;

                if (i < v) {
                    Edge e;
                    e.u = i;
                    e.v = v;
                    e.weight = w;
                    edges.push_back(e);
                }

                ++it1;
                ++it2;
            }
        }

        sort(edges.begin(), edges.end(), cmp);

        int parent[100];
        for (int i = 0; i < n; i++) parent[i] = i;

        int total = 0;

        vector<Edge>::iterator it;
        for (it = edges.begin(); it != edges.end(); ++it) {
            int u = it->u;
            int v = it->v;
            int w = it->weight;

            if (findParent(u, parent) != findParent(v, parent)) {
                cout << u << " - " << v << " : " << w << endl;
                total += w;
                unite(u, v, parent);
            }
        }

        cout << "Total = " << total << endl;
    }

    void Prim(int start) {
        int key[100];
        bool inMST[100];
        int parent[100];

        for (int i = 0; i < n; i++) {
            key[i] = 999999;
            inMST[i] = false;
            parent[i] = -1;
        }

        key[start] = 0;

        for (int count = 0; count < n - 1; count++) {
            int min = 999999, u = -1;

            for (int i = 0; i < n; i++) {
                if (!inMST[i] && key[i] < min) {
                    min = key[i];
                    u = i;
                }
            }

            inMST[u] = true;

            vector<int>::iterator it1 = adj[u].begin();
            vector<int>::iterator it2 = weight[u].begin();

            while (it1 != adj[u].end()) {
                int v = *it1;
                int w = *it2;

                if (!inMST[v] && w < key[v]) {
                    key[v] = w;
                    parent[v] = u;
                }

                ++it1;
                ++it2;
            }
        }

        int total = 0;
        for (int i = 0; i < n; i++) {
            if (parent[i] != -1) {
                cout << parent[i] << " - " << i << " : " << key[i] << endl;
                total += key[i];
            }
        }

        cout << "Total = " << total << endl;
    }
};

int main() {
    Graph g(5);

    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 3, 3);
    g.addEdge(2, 4, 7);
    g.addEdge(1, 4, 2);
    g.addEdge(4, 3, 3);

    g.showList();
    g.showMatrix();
    cout << "DFS: ";
    g.DFS(0);

    cout << "BFS: ";
    g.BFS(0);

    cout << "Kruskal:\n";
    g.Kruskal();

    cout << "Prim:\n";
    g.Prim(0);

    return 0;
}