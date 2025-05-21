#include <iostream>
#include <stack>
#include <vector>

using namespace std;

const int DIRE = 4;
const int dx[DIRE] = { 0, -1, 0, 1 };  
const int dy[DIRE] = { 1, 0, -1, 0 }; 
const char* dirNames[DIRE] = { "右", "上", "左", "下" };

struct Position {
    int x, y;      
    int dir;       // 下一步方向，0-右，1-上，2-左，3-下

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
        stack<Position> pathStack;  // 用栈来存储路径

        // 将入口点加入栈
        pathStack.push(start);
        visited[start.x][start.y] = true;

        // 当栈不为空时继续搜索
        while (!pathStack.empty()) {
            // 获取当前位置
            Position current = pathStack.top();

            // 如果到达出口，则找到了路径
            if (current.x == end.x && current.y == end.y) {
                printPath(pathStack);
                return true;
            }

            // 标记是否找到下一个可行的位置
            bool foundNextStep = false;

            // 尝试从当前方向继续探索
            for (int d = current.dir; d < DIRE; d++) {
                int newX = current.x + dx[d];
                int newY = current.y + dy[d];

                // 如果新位置有效且未被访问
                if (isValid(newX, newY) && !visited[newX][newY]) {
                    // 更新当前位置的方向，以便回溯时继续尝试
                    pathStack.top().dir = d + 1;

                    // 将新位置加入栈
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

        cout << "没有找到从入口到出口的路径！" << endl;
        return false;
    }

    // 打印找到的路径
    void printPath(stack<Position>& pathStack) {
        vector<Position> path;
        while (!pathStack.empty()) {
            path.push_back(pathStack.top());
            pathStack.pop();
        }
        reverse(path.begin(), path.end());
        cout << "找到从入口到出口的路径：" << endl;
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
    cout << "请输入迷宫的行数和列数: ";
    cin >> rows >> cols;
    vector<vector<int>> maze(rows, vector<int>(cols));

    cout << "请输入迷宫矩阵 (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> maze[i][j];
        }
    }
    int entranceX = 0, entranceY = 0;  // 左上角为入口
    int endX = cols-1, endY = rows-1;         // 右下角为出口

    MazeSolver solver(maze, entranceX, entranceY, endX, endY);
    solver.findPath();

    return 0;
}