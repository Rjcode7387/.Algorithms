#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>

#define X first
#define Y second

using namespace std;

int canvas[500][500];

int row, column;

int xDir[4] = { 1,0,-1,0 };
int yDir[4] = { 0,-1,0,1 };

bool vis[500][500];

void printcanvas(int canvas[500][500]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cout << canvas[i][j] << ' ';
        }
        if (i < row - 1) {
            cout << endl;
        }
    }
}

int main(void) {
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> row >> column;

    for (int x = 0; x < row; x++) {
        for (int y = 0; y < column; y++) {
            cin >> canvas[x][y];
        }
    }

    int nums = 0;
    int maxsize = 0;

    for (int x = 0; x < row; x++) {
        for (int y = 0; y < column; y++) {
            if (canvas[x][y] == 0 || vis[x][y]) continue;
            queue<pair<int, int>> Q;
            nums++;
            Q.push({ x,y });
            vis[x][y] = 1;
            int area = 0;
            while (!Q.empty()) {
                area++;
                pair<int, int> cur = Q.front();
                Q.pop();

                for (int dir = 0; dir < 4; dir++) {
                    int nx = cur.X + xDir[dir];
                    int ny = cur.Y + yDir[dir];
                    if (nx < 0 || nx >= row || ny < 0 || ny >= column) continue;
                    if (canvas[nx][ny] != 1 || vis[nx][ny]) continue;
                    vis[nx][ny] = 1;
                    Q.push({ nx,ny });
                }
                maxsize = max(maxsize, area);
            }
        }
    }

    cout << nums << '\n' << maxsize;
}