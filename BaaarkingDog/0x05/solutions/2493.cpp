// Authored by : twinkite
// Co-authored by : BaaaaaaaaaaarkingDog
// http://boj.kr/44465623025e452bba5feb80b0b0e60e
#include <bits/stdc++.h>
using namespace std;

// pair의 first, second 멤버를 더 직관적인 이름으로 사용하기 위한 매크로
#define X first   // X는 탑의 높이를 나타냄
#define Y second  // Y는 탑의 인덱스(위치)를 나타냄

int N;  // 탑의 개수를 저장할 변수
// pair<int,int>를 저장하는 스택 선언
// first(X): 탑의 높이, second(Y): 탑의 인덱스(위치)
stack<pair<int, int>> tower;

int main() {
  // 입출력 최적화
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  cin >> N;  // 탑의 개수 입력받기

  // 초기 보초값 설정
  // {100000001, 0}: 높이가 매우 큰 가상의 탑을 추가
  // 이렇게 하면 스택이 비어있는 경우를 따로 처리할 필요가 없음
  tower.push({ 100000001, 0 });

  // 각 탑을 순서대로 처리
  for (int i = 1; i <= N; i++) {
    int height;  // 현재 탑의 높이를 저장할 변수
    cin >> height;  // 현재 탑의 높이 입력받기

    // 스택의 top에 있는 탑의 높이가 현재 탑보다 작은 동안
    // 스택에서 제거 (더 작은 탑들은 이후의 탑들에 대해서도 의미가 없음)
    while (tower.top().X < height)
      tower.pop();

    // 현재 스택의 top에 있는 탑이 현재 탑보다 큰 첫 번째 탑
    // 이 탑의 인덱스가 현재 탑의 신호를 수신할 수 있는 탑의 위치
    cout << tower.top().Y << " ";

    // 현재 탑을 스택에 추가
    // 이후의 탑들에 대해 이 탑이 수신 가능한 탑이 될 수 있음
    tower.push({ height, i });
  }

}