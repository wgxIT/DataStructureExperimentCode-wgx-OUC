#include <iostream>
#include <stack>
#include <vector>

using namespace std;

const int DIRE = 4;
const int dx[DIRE] = { 0, -1, 0, 1 };  
const int dy[DIRE] = { 1, 0, -1, 0 }; 
const char* dirNames[DIRE] = { "��", "��", "��", "��" };

struct Position {
    int x, y;      
    int dir;       // ��һ������0-�ң�1-�ϣ�2-��3-��

    Position(int x = 0, int y = 0, int dir = 0) : x(x), y(y), dir(dir) {}   
};



class MazeSolver {
private:
    vector<vector<int>> maze;   
    int rows, cols;            
    Position start;             
    Position end;              
    vector<vector<bool>> visited;  

public:
    MazeSolver(const vector<vector<int>>& m, int startX, int startY, int endX, int endY) {
        maze = m;
        rows = maze.size();
        cols = maze[0].size();
        start = Position(startX, startY);
        end = Position(endX, endY);

       
        visited.resize(rows, vector<bool>(cols, false));
    }

    bool isValid(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] == 0;
    }

    bool findPath() {
        stack<Position> pathStack;  // ��ջ���洢·��

        // ����ڵ����ջ
        pathStack.push(start);
        visited[start.x][start.y] = true;

        // ��ջ��Ϊ��ʱ��������
        while (!pathStack.empty()) {
            // ��ȡ��ǰλ��
            Position current = pathStack.top();

            // ���������ڣ����ҵ���·��
            if (current.x == end.x && current.y == end.y) {
                printPath(pathStack);
                return true;
            }

            // ����Ƿ��ҵ���һ�����е�λ��
            bool foundNextStep = false;

            // ���Դӵ�ǰ�������̽��
            for (int d = current.dir; d < DIRE; d++) {
                int newX = current.x + dx[d];
                int newY = current.y + dy[d];

                // �����λ����Ч��δ������
                if (isValid(newX, newY) && !visited[newX][newY]) {
                    // ���µ�ǰλ�õķ����Ա����ʱ��������
                    pathStack.top().dir = d + 1;

                    // ����λ�ü���ջ
                    pathStack.push(Position(newX, newY));
                    visited[newX][newY] = true;

                    foundNextStep = true;
                    break;
                }
            }

            if (!foundNextStep) {
                pathStack.pop();
            }
        }

        cout << "û���ҵ�����ڵ����ڵ�·����" << endl;
        return false;
    }

    // ��ӡ�ҵ���·��
    void printPath(stack<Position>& pathStack) {
        vector<Position> path;
        while (!pathStack.empty()) {
            path.push_back(pathStack.top());
            pathStack.pop();
        }
        reverse(path.begin(), path.end());
        cout << "�ҵ�����ڵ����ڵ�·����" << endl;
        for (size_t i = 0; i < path.size() - 1; i++) {
            cout << "(" << path[i].x << ", " << path[i].y << ") -> ";

            int dirIndex = -1;
            for (int d = 0; d < DIRE; d++) {
                if (path[i].x + dx[d] == path[i + 1].x && path[i].y + dy[d] == path[i + 1].y) {
                    dirIndex = d;
                    break;
                }
            }

            if (dirIndex >= 0) {
                cout << dirNames[dirIndex] << " -> ";
            }
        }
        cout << "(" << path.back().x << ", " << path.back().y << ")" << endl;
    }
};

int main() {
    int rows, cols;
    cout << "�������Թ�������������: ";
    cin >> rows >> cols;
    vector<vector<int>> maze(rows, vector<int>(cols));

    cout << "�������Թ����� (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> maze[i][j];
        }
    }
    int entranceX = 0, entranceY = 0;  // ���Ͻ�Ϊ���
    int endX = cols-1, endY = rows-1;         // ���½�Ϊ����

    MazeSolver solver(maze, entranceX, entranceY, endX, endY);
    solver.findPath();

    return 0;
}