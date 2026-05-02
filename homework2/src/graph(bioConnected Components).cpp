#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stack>

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
    int bccCount; //用來計算 Biconnected Component 的數量
    vector<int>* adj;
    Node** linkedAdj;     

    // --- 為 Biconnected 新增的變數 ---
    vector<int> dfn;
    vector<int> low;
    stack<Edge> s; // 用來儲存邊

    // 計算 dfn, low 並用堆疊找出 Biconnected Component
    void Biconnected(int u, int v) {
        dfn[u] = low[u] = num++;
        
        for (int w : adj[u]) {
            
            // 情況 1: Tree edge (尚未被探索過)
            if (dfn[w] == 0) {
                s.push({ u, w });   // 先 push (將邊加入堆疊)
                Biconnected(w, u);

                low[u] = min(low[u], low[w]); // 更新 low 值

                // 判斷是否為關節點條件以劃分區塊 (Articulation condition)
                if (low[w] >= dfn[u]) {
                    bccCount++; //增加編號計數
                    cout << "Biconnected Component " << bccCount << ":\n"; //印出編號
                    Edge e;
                    do {
                        e = s.top(); 
                        s.pop();
                        cout << "  (" << e.u << ", " << e.v << ")" << endl;
                    } while (!( (e.u == u && e.v == w) || (e.u == w && e.v == u) )); // 確保彈出到當前的邊為止
                    
                }
            }
            // 情況 2: Back edge（只處理往祖先，避免父親節點重複處理）
            else if (w != v && dfn[w] < dfn[u]) {
                s.push({ u, w });   // 回邊也要推入堆疊，它是構成 Cycle 的重要邊
                low[u] = min(low[u], dfn[w]);
            }
        }
    }

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

    // 啟動 Biconnected 演算法的外部函式 
    void Biconnected() {
        num = 1;
        bccCount = 0; // ⭐ 在每一次啟動計算前，將 Component 數量歸零初始化
        
        // 現代 C++ 寫法取代原圖片中 new / fill / delete 的指標陣列操作
        dfn.assign(n, 0); 
        low.assign(n, 0);
        
        // 清空堆疊確保狀態乾淨
        while (!s.empty()) s.pop();

        
        // 為了處理可能不連通的多個元件，這裡用迴圈檢查每一個節點
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
    g.Components(); // 顯示所有連通分支

    cout << "\nBiconnected Components:" << endl;
    g.Biconnected(); // 顯示所有 Biconnected Components

    return 0;
}