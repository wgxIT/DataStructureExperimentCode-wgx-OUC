#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

const int INF = 1e9; // ��ʾ�����
int n;               
vector<string> names;         
vector<string> descriptions;  
vector<vector<int>> adjMatrix;  // �ڽӾ���

// ��ʼ��ͼ
void initGraph() {
    cout << "�����뾰������ n��";
    cin >> n;
    names.resize(n);
    descriptions.resize(n);
    adjMatrix.assign(n, vector<int>(n, INF));

    cout << "������ÿ���������Ϣ����ʽ������ ��飩��" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "��" << i+1 << "�ž��㣺";
        cin >> names[i];
        getline(cin, descriptions[i]);
    }

    cout << "��������� m��";
    int m;
    cin >> m;
    cout << "������ÿ���ߵ���Ϣ����ʽ������� �յ��� ���룩��" << endl;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adjMatrix[u-1][v-1] = w;
        adjMatrix[v-1][u-1] = w; // ����ͼ
    }
}

// ��ѯ������Ϣ
void querySpotInfo(int id) {
    if (id <= 0 || id > n) {
        cout << "��������Ч��" << endl;
        return;
    }
    cout << "���: " << id << "\n����: " << names[id-1] << "\n���: " << descriptions[id-1] << endl;
}

// Dijkstra �㷨�������·��
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
        cout << "�޷�����þ��㡣" << endl;
        return;
    }

    // ���·��
    vector<int> path;
    for (int v = end; v != -1; v = prev[v])
        path.push_back(v);

    cout << "���·��Ϊ��";
    for (int i = path.size() - 1; i >= 0; --i) {
        cout << names[path[i]];
        if (i > 0) cout << " -> ";
    }
    cout << "\n�ܾ���: " << dist[end] << " ��" << endl;
}

// �˵�����
void menu() {
    while (true) {
        cout << "\nУ԰����ϵͳ�˵�\n";
        cout << "1. ��ѯ������Ϣ\n";
        cout << "2. ��ѯ���·��\n";
        cout << "3. �˳�ϵͳ\n";
        cout << "������ѡ�";
        int choice;
        cin >> choice;

        if (choice == 1) {
            int id;
            cout << "�����뾰���� (0 ~ " << n - 1 << ")��";
            cin >> id;
            querySpotInfo(id);
        }
        else if (choice == 2) {
            int from, to;
            cout << "����������ź��յ��ţ��Կո�ָ�����";
            cin >> from >> to;
            dijkstra(from-1, to-1);
        }
        else if (choice == 3) {
            cout << "��лʹ�ã��ټ���" << endl;
            break;
        }
        else {
            cout << "��Ч��ѡ����������롣" << endl;
        }
    }
}

int main() {
    initGraph();
    menu();
    return 0;
}
