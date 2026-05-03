//41343119

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stack>

using namespace std;


struct Edge {
    int u, v;
};

struct Node {
    int dest;
    Node* next;
    Node(int d) : dest(d), next(nullptr) {}
};

class Graph {
private:
    int n;
    int num;
    int bccCount; 
    vector<int>* adj;
    Node** linkedAdj;     

    vector<int> dfn;
    vector<int> low;
    stack<Edge> s; //儲存邊

    // 計算dfn用堆疊找Biconnected Component
    void Biconnected(int u, int v) {
        dfn[u] = low[u] = num++;
        
        for (int w : adj[u]) {
            
            //Tree edge沒探索過
            if (dfn[w] == 0) {
                s.push({ u, w });   
                Biconnected(w, u);

                low[u] = min(low[u], low[w]);

                if (low[w] >= dfn[u]) {
                    bccCount++; 
                    cout << "Biconnected Component " << bccCount << ":\n";
                    Edge e;
                    do {
                        e = s.top(); 
                        s.pop();
                        cout << "  (" << e.u << ", " << e.v << ")" << endl;
                    } while (!( (e.u == u && e.v == w) || (e.u == w && e.v == u) )); 
                    
                }
            }
            else if (w != v && dfn[w] < dfn[u]) {
                s.push({ u, w });   
                low[u] = min(low[u], dfn[w]);
            }
        }
    }

public:
    Graph(int nodes) : n(nodes) {
        adj = new vector<int>[n];
        
        linkedAdj = new Node*[n];
        for (int i = 0; i < n; i++) {
            linkedAdj[i] = nullptr;
        }
    }

    ~Graph() {
        delete[] adj;
        
        for (int i = 0; i < n; ++i) {
            Node* current = linkedAdj[i];
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] linkedAdj;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); 
       
        //加入至 Linked Adjacency Lists
        Node* newNode = new Node(v);
        if (linkedAdj[u] == nullptr) {
            linkedAdj[u] = newNode;
        } else {
            Node* temp = linkedAdj[u];
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    
    void showMartix() {
        vector<int>::iterator it;
        cout <<"  ";
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

    // 顯示Linked Adjacency Lists
    void showLinkedlist() {
        for (int i = 0; i < n; ++i) {
            cout << i << " : ";
            Node* temp = linkedAdj[i];
            while (temp != nullptr) {
                cout << temp->dest << " -> ";
                temp = temp->next;
            }
            cout << "NULL" << endl;
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

    void Components() {
        vector<bool> visited(n, false);
        int componentCount = 0;

        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                componentCount++;
                cout << "Component " << componentCount << ": ";
                
                DFS_util(i, visited); 
                
                cout << endl;
            }
        }
    }

    void Biconnected() {
        num = 1;
        bccCount = 0; 
        
        dfn.assign(n, 0); 
        low.assign(n, 0);
        
        while (!s.empty()) s.pop();

        
        for(int i = 0; i < n; i++) {
            if (dfn[i] == 0) {
                Biconnected(i, -1);
            }
        }
    }
};

int main() {
    
    Graph g(10);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(4, 3);
    g.addEdge(3, 5);
    g.addEdge(5, 6);
    
    g.addEdge(7, 8);
    g.addEdge(7, 9);
    
    cout << "Array Adjacency Lists:" << endl;
    g.showArraylist();
    
    cout << "\nLinked Adjacency Lists:" << endl;
    g.showLinkedlist(); // 呼叫Linked list

    cout << "\nAdjacency Matrix:" << endl;
    g.showMartix();
    
    cout << "\nDFS:" << endl;
    g.DFS(0);

    cout << "\nComponents:" << endl;
    g.Components(); 

    cout << "\nBiconnected Components:" << endl;
    g.Biconnected(); 
    return 0;
}
