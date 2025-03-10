#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
#include <windows.h>

using namespace std;
using namespace std::chrono;

int N;
vector<vector<int>> board;
vector<vector<int>> result;
vector<vector<int>> bestResult;
int minSquares = 400;

int oneCount = 0;
unsigned long long operationsCount = 0;

bool canPlace(int x, int y, int w) {
    if (x + w > N || y + w > N)
        return false;
    for (int i = x; i < x + w; ++i) {
        for (int j = y; j < y + w; ++j) {
        if (board[i][j] != 0)
            return false;
        }
    }
    return true;
}

void placeSquare(int x, int y, int w) {
    operationsCount++;
    for (int i = x; i < x + w; ++i) {
        for (int j = y; j < y + w; ++j) {
        board[i][j] = 1;
        }
    }
}

void removeSquare(int x, int y, int w) {
    // operationsCount++;
    for (int i = x; i < x + w; ++i) {
        for (int j = y; j < y + w; ++j) {
        board[i][j] = 0;
        }
    }
}

void backtrack(int x, int y, int squaresUsed) {
    // operationsCount++;
    if (squaresUsed >= minSquares)
        return;

    if (N > 7) {
        if (oneCount > (N / 4)) {
        return;
        }
    }

    if (x == N) {
        minSquares = squaresUsed;
        bestResult = result;
        return;
    }

    if (y == N) {
        backtrack(x + 1, 0, squaresUsed);
        return;
    }

    if (board[x][y] != 0) {
        backtrack(x, y + 1, squaresUsed);
        return;
    }

    for (int w = min(N - x, N - y); w >= 1; --w) {
        if (x == 0 && y == 0 && w < (N - 1) / 2) {
            break;
        }
        if (w == N)
        continue;
        if (canPlace(x, y, w)) {
        placeSquare(x, y, w);
        result.push_back({x + 1, y + 1, w});
        if (w == 1) {
            oneCount++;
        }
        backtrack(x, y + w, squaresUsed + 1);
        result.pop_back();
        if (w == 1) {
            oneCount--;
        }
        removeSquare(x, y, w);
        }
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cin >> N;
    board.resize(N, vector<int>(N, 0));

    auto start = high_resolution_clock::now();
    backtrack(0, 0, 0);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << minSquares << endl;
    for (auto& sq : bestResult) {
        cout << sq[0] << " " << sq[1] << " " << sq[2] << endl;
    }

    cout << "Время выполнения: " << duration.count() << " мс" << endl;
    cout << "Всего операций: " << operationsCount << endl;

    return 0;
}