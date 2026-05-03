# 第九組:41343119、41343128
# 41343128 陳廷鑫
Graph 
## 解題說明
負責實作的部分:
1. Adjacency List、Adjacency Matrix
2. BFS、DFS
3. Weighted
4. Spanning Trees:Kruskal’s Algorithm、Prim’s Algorithm
### 解題策略和步驟
1. 使用 vector<int>來儲存點之間的關係還有距離
2. DFS使用遞迴，先標記自己然後找鄰居，走到底之後再回來，直到所有的點都被看過。
3. BFS用了queue，從起點開始，把鄰居都先放進queue，再從裡面一個一個的找鄰居
4. Kruskal先找出所有的邊用距離排好，從距離最小的邊開始，如果會形成迴圈就不要選
5. Prim找一個起點，從起點開始找距離最短的邊，選到下一個點，然後重複

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
            int v = *it1; // 鄰居
            int w = *it2; // 邊的距離


            if (i < v) {     // 避免重複加入
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

    sort(edges.begin(), edges.end(), cmp);     //照距離排序

    int parent[100];
    for (int i = 0; i < n; i++) parent[i] = i;

    int total = 0;

    vector<Edge>::iterator it;
    for (it = edges.begin(); it != edges.end(); ++it) {
        int u = it->u;
        int v = it->v;
        int w = it->weight;

        if (findParent(u, parent) != findParent(v, parent)) {          // 不會形成迴圈才加入
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
    int key[100]; // 存目前加入的最小邊距離
    bool inMST[100]; // 存這個點有沒有已經在MST裡
    int parent[100]; // 存每個點是從哪個點連進來的

    for (int i = 0; i < n; i++) {
        key[i] = 999999;
        inMST[i] = false;
        parent[i] = -1;
    }

    key[start] = 0;

    for (int count = 0; count < n - 1; count++) {
        int min = 999999, u = -1;

        for (int i = 0; i < n; i++) {  // 找還沒在MST中且key最小的點
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

* **時間複雜度**：
1. DFS:O(V + E)
2. BFS:O(V + E)
3. Kruskal:O(E log E)
4. Prim:O(V²)
## 測試與驗證

### 測試案例
```cpp
Graph g(5);

g.addEdge(0, 1, 1);
g.addEdge(0, 2, 2);
g.addEdge(1, 3, 3);
g.addEdge(2, 4, 7);
g.addEdge(1, 4, 2);
g.addEdge(4, 3, 3);
```
```cpp
結果
List:
0 : 1(w:1) 2(w:2)
1 : 0(w:1) 3(w:3) 4(w:2)
2 : 0(w:2) 4(w:7)
3 : 1(w:3) 4(w:3)
4 : 2(w:7) 1(w:2) 3(w:3)
Matrix:
  0 1 2 3 4
0 0 1 2 0 0
1 1 0 0 3 2
2 2 0 0 0 7
3 0 3 0 0 3
4 0 2 7 3 0
DFS: 0 1 3 4 2
BFS: 0 1 2 3 4
Kruskal:
0 - 1 : 1
0 - 2 : 2
1 - 4 : 2
1 - 3 : 3
Total = 8
Prim:
0 - 1 : 1
0 - 2 : 2
1 - 3 : 3
1 - 4 : 2
Total = 8
```
### 結論
在程式實作中，圖的基本表示方式，包含Adjacency List與Adjacency Matrix兩種表示法，還有點之間的距離。
在圖的走訪部分，透過 DFS 與 BFS 能驗證節點的連通性還有順序；在最小生成樹部分，Kruskal 與 Prim 演算法都可以正確求最小距離的生成樹，並透過不同方式達到相同目標。

## 申論及開發報告

在本次實作圖的功能過程中，主要從最基本的圖表示的程式開始改，慢慢加入要寫的功能。
一開始在作圖的結構時，使用單一陣列來儲存邊，但在DFS與BFS時發現不易管理兩點之間的關係，改用adjacency list，並加另一個vector儲存距離(就是權重)，使資料結構更清楚且方便操作，
在 DFS 的實作過程中，主要在於如何避免重複拜訪同一個點，使用visited陣列來標記已走過的節點，並透過遞迴方式搜尋所有可到達的節點。一開始容易出現無限遞迴的問題，
BFS 的部分則使用queue來實作階層式走訪，
在最小生成樹的部分，Kruskal需要先將所有邊收集並排序，因此使用sort搭配額外的比較函式，Prim 演算法則是從一個起點開始逐步擴展，每次選擇距離最短的邊加入生成樹，在寫程式的過程中，透過不斷測試與修正錯誤
，慢慢完成 DFS、BFS 與spanning tree等核心功能，也更理解不同演算法的方式。
# 41343119 金宗翰
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
  1. Linked Adjacency Lists: $O(V + E)$
  2. Connected Components: $O(V)$
  3. Bioconnect Components: $O(V + E)$
* **時間複雜度**：
  1. Linked Adjacency Lists: $O(V + E)$
  2. Connected Components: $O(V + E)$
  3. Bioconnect Components: $O(V + E)$
## 測試與驗證

### 測試案例
<img width="281" height="250" alt="image" src="https://github.com/user-attachments/assets/fcc4272b-11ca-4ee5-ac06-0d6c890e9c80" />
<img width="329" height="77" alt="image" src="https://github.com/user-attachments/assets/52ac98f3-5b5b-4026-b4cd-7c6aea4b831a" />
<img width="304" height="382" alt="image" src="https://github.com/user-attachments/assets/cb221353-cc3d-42e8-9cef-f73adca5bcc1" />


### 結論



1.	相鄰串列 (Adjacency Lists)」，能避免了矩陣的空間浪費，確保時間與空間複雜度皆達到最優的 $O(V+E)$。
2.	連通分支 (Connected Components)利用基礎的 DFS (深度優先搜尋)，能正確且有效地找出圖中彼此獨立的子圖。
3.	雙連通分量 (Biconnected Components)結合了 Tarjan 演算法（利用 dfn 與 low 判斷關節點）與堆疊 (Stack) 結構。能找出彼此獨立的子圖。








