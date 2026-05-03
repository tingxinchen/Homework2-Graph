//41343119

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;


struct Edge {
    int u, v;
};

//用於 Linked Adjacency Lists 的節點結構
struct Node {
    int dest;
    Node* next;
    Node(int d) : dest(d), next(nullptr) {}
};

class Graph {
private:
    int n;
    int num;
    vector<int>* adj;
    Node** linkedAdj;     //用於Linked Adjacency Lists

public:
    Graph(int nodes) : n(nodes) {
        adj = new vector<int>[n];
        
        //初始化 Linked Adjacency Lists
        linkedAdj = new Node*[n];
        for (int i = 0; i < n; i++) {
            linkedAdj[i] = nullptr;
        }
    }

    ~Graph() {
        delete[] adj;
        
        //釋放 Linked Adjacency Lists 的記憶體
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

    // 尋找並印出圖中的所有連通分支 (Connected Components)
    void Components() {
        // 初始化 visited，所有頂點預設為尚未訪問
        vector<bool> visited(n, false);
        int componentCount = 0;

        
        for (int i = 0; i < n; i++) {
            // 如果該頂點尚未被訪問，代表發現了一個新的連通分支
            if (!visited[i]) {
                componentCount++;
                cout << "Component " << componentCount << ": ";
                
                // 進行 DFS 找出這個 component 的所有頂點
                DFS_util(i, visited); 
                
                //換行以區隔不同的連通分支
                cout << endl;
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
    g.Components(); // 顯示所有連通分支
    return 0;
}
