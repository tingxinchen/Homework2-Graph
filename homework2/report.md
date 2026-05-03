# 41343119
Graph 
## 解題說明
實作的部分:
1. Linked Adjacency Lists
2. Connected Components
3. Bioconnect Components
### 解題策略和步驟


## 程式實作
以下是程式碼：
```cpp

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








