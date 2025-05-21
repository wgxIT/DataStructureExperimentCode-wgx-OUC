#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

const int INF = 1e9; // 表示无穷大
int n;               
vector<string> names;         
vector<string> descriptions;  
vector<vector<int>> adjMatrix;  // 邻接矩阵

// 初始化图
void initGraph() {
    cout << "请输入景点数量 n：";
    cin >> n;
    names.resize(n);
    descriptions.resize(n);
    adjMatrix.assign(n, vector<int>(n, INF));

    cout << "请输入每个景点的信息（格式：名称 简介）：" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "第" << i+1 << "号景点：";
        cin >> names[i];
        getline(cin, descriptions[i]);
    }

    cout << "请输入边数 m：";
    int m;
    cin >> m;
    cout << "请输入每条边的信息（格式：起点编号 终点编号 距离）：" << endl;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adjMatrix[u-1][v-1] = w;
        adjMatrix[v-1][u-1] = w; // 无向图
    }
}

// 查询景点信息
void querySpotInfo(int id) {
    if (id <= 0 || id > n) {
        cout << "景点编号无效。" << endl;
        return;
    }
    cout << "编号: " << id << "\n名称: " << names[id-1] << "\n简介: " << descriptions[id-1] << endl;
}

// Dijkstra 算法查找最短路径
void dijkstra(int start, int end) {
    vector<int> dist(n, INF);
    vector<bool> visited(n, false);
    vector<int> prev(n, -1);

    dist[start] = 0;

    for (int i = 0; i < n; ++i) {
        int u = -1;
        int minDist = INF;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && dist[j] < minDist) {
                u = j;
                minDist = dist[j];
            }
        }

        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < n; ++v) {
            if (!visited[v] && adjMatrix[u][v] != INF) {
                if (dist[v] > dist[u] + adjMatrix[u][v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    prev[v] = u;
                }
            }
        }
    }

    if (dist[end] == INF) {
        cout << "无法到达该景点。" << endl;
        return;
    }

    // 输出路径
    vector<int> path;
    for (int v = end; v != -1; v = prev[v])
        path.push_back(v);

    cout << "最短路径为：";
    for (int i = path.size() - 1; i >= 0; --i) {
        cout << names[path[i]];
        if (i > 0) cout << " -> ";
    }
    cout << "\n总距离: " << dist[end] << " 米" << endl;
}

// 菜单界面
void menu() {
    while (true) {
        cout << "\n校园导游系统菜单\n";
        cout << "1. 查询景点信息\n";
        cout << "2. 查询最短路径\n";
        cout << "3. 退出系统\n";
        cout << "请输入选项：";
        int choice;
        cin >> choice;

        if (choice == 1) {
            int id;
            cout << "请输入景点编号 (0 ~ " << n - 1 << ")：";
            cin >> id;
            querySpotInfo(id);
        }
        else if (choice == 2) {
            int from, to;
            cout << "请输入起点编号和终点编号（以空格分隔）：";
            cin >> from >> to;
            dijkstra(from-1, to-1);
        }
        else if (choice == 3) {
            cout << "感谢使用，再见！" << endl;
            break;
        }
        else {
            cout << "无效的选项，请重新输入。" << endl;
        }
    }
}

int main() {
    initGraph();
    menu();
    return 0;
}
