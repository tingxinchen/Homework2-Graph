# 41343119
Graph 
## 解題說明
實作的部分:
1. Linked Adjacency Lists
2. Connected Components
3. Bioconnect Components
### 解題策略和步驟
1. 相鄰串列 (Adjacency List)
    1.	初始化：建立一個大小為節點總數 $V$ 的陣列，陣列的每一格用來存放一個串列 (Linked List 或 vector)。
    2.	加入邊 (u, v)：當收到一條連接 u 和 v 的邊時，建立一個包含 v 的新節點。
    3.	雙向安插：把這個新節點插入 u 的串列最前方（頭部插入，效能最好）。因為是無向圖，同理也要把 u 插入 v 的串列中。
2. 連通分支 (Connected Components)
    1.	建立標記：準備一個 visited 陣列，把所有點預設為「未訪問」(false)。
    2.	找未訪問點：用迴圈掃描每一個點。如果遇到「未訪問」的點，代表發現了一個全新的連通區塊。
    3.	擴散搜尋 (DFS)：從這個新點啟動 DFS，把所有能沿著邊走到的點都標記為「已訪問」。
    4.	重複尋找：迴圈繼續尋找下一個未訪問的點，直到全圖的點都被走過為止。
3. 雙連通分量 (Biconnected Components)
    1.	準備變數：準備時間戳記 dfn 陣列、回退極限 low 陣列，以及一個用來裝「邊」的 Stack。
    2.	探索與存邊：
        *	走DFS時，給當前節點發配 dfn 與 low 值。
        *	看到往前的新路 (Tree Edge) 或往回的舊路 (Back Edge)，都把這條邊丟進 Stack，並更新自己的 low。

## 程式實作
以下是程式碼：
```cpp
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
```
##效能分析

* **空間複雜度**：
## 測試與驗證

### 測試案例


### 結論



## 申論及開發報告


# 41343128 陳廷鑫
Graph 
## 解題說明
實作的部分:
1. Adjacency List、Adjacency Matrix
2. BFS、DFS
3. Weighted
4. Spanning Trees:Kruskal’s Algorithm、Prim’s Algorithm
### 解題策略和步驟


## 程式實作
以下是程式碼：
### Adjacency List
```cpp
vector<int> adj[100];     
vector<int> weight[100];
```

### Adjacency List
```cpp
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
```
### Adjacency Matrix
```cpp
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
```

### DFS
```cpp
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
```

### BFS
```cpp
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
```

### Kruskal
```cpp
void Kruskal() {
    vector<Edge> edges;

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
```

### Prim
```cpp
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
```
## 效能分析

* **空間複雜度**：
## 測試與驗證

### 測試案例


### 結論



## 申論及開發報告








