/*有附帶權重

*/





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
    vector<pair<int, int>>* adj;

public:
    Graph(int nodes) : n(nodes) {
        adj = new vector<pair<int, int>>[n];
    }

    ~Graph() {
        delete[] adj;
    }

    void addEdge(int u, int v,int weight) {
        adj[u].push_back({ v, weight });
        adj[v].push_back({ u, weight });

    }

    void showMartix() {
        cout << "  ";
        for (int k = 0; k < n; k++) cout << k << " ";
        cout << endl;

        for (int i = 0; i < n; ++i) {
            cout << i << " ";
            for (int j = 0; j < n; j++) {
                bool found = false;
                vector<pair<int, int>>::iterator it;

                for (it = adj[i].begin(); it < adj[i].end(); ++it) {
                    if (it->first == j) {
                        cout << it->second << " "; // 權重
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "0 ";
            }
            cout << endl;
        }
    }
    void showArraylist() {
        vector<pair<int, int>>::iterator it;
        for (int i = 0; i < n; ++i) {
            cout << i << " : ";
            for (it = adj[i].begin(); it < adj[i].end(); ++it)
                cout << it->first << "w:" << it->second << "  ";
            cout << endl;
        }
    }
    void DFS_util(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        vector<pair<int, int>>::iterator it;
        for (it = adj[v].begin(); it < adj[v].end(); ++it) {
            int next_node = it->first; 
            if (!visited[next_node]) {
                DFS_util(next_node, visited);
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

        // 處理起點
        visited[start] = true;
        q.push(start);

        cout << "BFS: ";

        while (!q.empty()) {
            // 目前要處理的點
            int v = q.front();
            q.pop();
            cout << v << " ";

            // 檢查鄰居
            // 這裡必須使用明確的迭代器型別：vector<pair<int, int>>::iterator
            vector<pair<int, int>>::iterator it;
            for (it = adj[v].begin(); it != adj[v].end(); ++it) {
                // 因為現在 adj 存的是 pair<目的地, 權重>
                // 所以要透過 it->first 取得鄰居的編號
                int w = it->first;

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
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 3, 3);
    g.addEdge(2, 4, 4);

    g.showArraylist();
    g.showMartix();
    cout << endl;

    cout << "DFS:";
    g.DFS(0);
    cout << "BFS:";
    g.BFS(0);
    return 0;
}
