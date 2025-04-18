#include <bits/stdc++.h>
#define X first
#define Y second

using namespace std;

string board[102];
int dist[102][102];

int n, m;

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

int main(void) {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> board[i];
    }

    // 2차원 배열 메모리 구조:
    // 1. dist는 전체 2차원 배열의 시작 주소를 가리키는 포인터.
    // 2. dist[i]는 i번째 행의 시작 주소를 가리키는 포인터. 즉, &dist[i][0]과 동일.
    // 3. dist[i][j]는 i행 j열에 있는 실제 값(정수).
    //
    // 아래 코드에서:
    // - dist[i]는 i번째 행의 시작 주소 (포인터)
    // - dist[i]+m은 i번째 행에서 m개 요소 이후의 주소 (포인터)
    // - fill()은 시작 주소부터 끝 주소 사이의 모든 메모리를 -1로 초기화
    //
    // 결과적으로 dist[i][0]부터 dist[i][m-1]까지 모든 요소가 -1로 설정.
    for (int i = 0; i < n; i++) {
        fill(dist[i], dist[i] + m, -1);
    }

    queue<pair<int, int>> Q;
    Q.push({ 0,0 });

    dist[0][0] = 1;

    while (!Q.empty()) {
        auto cur = Q.front(); Q.pop();

        for (int dir = 0; dir < 4; dir++) {
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (dist[nx][ny] >= 0 || board[nx][ny] != '1') continue;

            // 현재 위치(cur.X, cur.Y)까지의 거리에 1을 더해 다음 위치(nx, ny)의 거리 값 설정
            // 이 값은 시작점(0,0)에서 (nx, ny)까지의 최단 거리를 의미
            // BFS 특성상 처음 방문할 때 설정된 거리가 항상 최단 거리임을 보장
            dist[nx][ny] = dist[cur.X][cur.Y] + 1;

            Q.push({ nx,ny });
        }
    }
    cout << dist[n - 1][m - 1];
}