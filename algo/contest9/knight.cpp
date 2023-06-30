#include "ReadWriter.h"

using namespace std;

long long fillField(int x, int y, long long **field, int n, int m);

long long move(int x, int y, long long **field, int n, int m) {
    long long move = field[x][y];

    if (move == -1) {
        move = fillField(x, y, field, n, m);
        field[x][y] = move;
    } else if (x == 0 && y == 0) {
        move = fillField(x, y, field, n, m);
    }

    return move;
}

long long fillField(int x, int y, long long **field, int n, int m) {
    if (x < 0 || y < 0 || x >= n || y >= m)
        return 0;

    if (field[x][y] == 0)
        return 1;

    long long firstMove = 0;
    long long secondMove = 0;
    long long thirdMove = 0;
    long long fourthMove = 0;

    if (!(x - 2 < 0 || y - 1 < 0)) {
        firstMove = move(x - 2, y - 1, field, n, m);
    }

    if (!(x - 2 < 0 || y + 1 >= m)) {
        secondMove = move(x - 2, y + 1, field, n, m);
    }

    if (!(x - 1 < 0 || y - 2 < 0)) {
        thirdMove = move(x - 1, y - 2, field, n, m);
    }

    if (!(x + 1 >= n || y - 2 < 0)) {
        fourthMove = move(x + 1, y - 2, field, n, m);
    }

    return firstMove + secondMove + thirdMove + fourthMove;
}

//Задача реализовать этот метод
//param N - количество строк (rows) доски
//param M - количество столбцов (columns) доски
//return - количество способов попасть в правый нижний угол доски (клетка N-1, M-1, если считать что первая клетка 0,0)
long long solve(int n, int m) {
    auto **field = new long long *[n];

    for (int i = 0; i < n; i++)
        field[i] = new long long[m]{0};

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            field[i][j] = -1;

    field[0][0] = 0;

    long long ans = fillField(n - 1, m - 1, field, n, m);

    for (int i = 0; i < n; i++)
        delete[] field[i];
    delete[] field;

    return ans;
}

int main(int argc, const char *argv[]) {
    ReadWriter rw;

    int N = rw.readInt(); //количество строк (rows)
    int M = rw.readInt(); //количество столбцов (columns)
    //решение
    long long res = solve(N, M);
    //результат в файл
    rw.writeLongLong(res);

    return 0;
}