#include "ReadWriter.h"

using namespace std;

void stonesTable(int **A, int *stones, int w, int n) {
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < w + 1; j++) {
            if (j - stones[i - 1] >= 0) {
                A[i][j] = max(A[i - 1][j], A[i - 1][j - stones[i - 1]] + stones[i - 1]);
            } else {
                A[i][j] = A[i - 1][j];
            }
        }
    }
}

void getStones(int **A, int *stones, int i, int j, vector<int> &res) {
    if (A[i][j] == 0)
        return;

    if (A[i][j] != A[i - 1][j]) {
        getStones(A, stones, i - 1, j - stones[i - 1], res);
        res.push_back(stones[i - 1]);
    } else {
        getStones(A, stones, i - 1, j, res);
    }
}

//Задача реализовать этот метод
//param n - количество камней
//param M - ограничения на вес
//param stonesTable - массив размера n, с весами камней
//param res - вектор результатов (вес камней, которые надо взять)
void solve(int n, int w, int *stones, vector<int> &res) {
    int **A = new int *[n + 1];

    for (int i = 0; i < n + 1; i++)
        A[i] = new int[w + 1]{0};

    stonesTable(A, stones, w, n);
    getStones(A, stones, n, w, res);

    for (int i = 0; i < n + 1; i++)
        delete[] A[i];
    delete[] A;
}

int main(int argc, const char *argv[]) {
    ReadWriter rw;
    int N = rw.readInt(); //камни
    int W = rw.readInt(); //ограничения на вес
    int *arr = new int[N]; //имеющиеся камни
    rw.readArr(arr, N);

    //основной структурой выбран вектор, так как заранее неизвестно какое количество камней будет взято
    vector<int> res;
    //решаем задачу
    solve(N, W, arr, res);
    int sum = 0;
    for (int i = 0; i < res.size(); i++)
        sum += res.at(i);

    //записываем ответ в файл
    rw.writeInt(sum); //итоговый вес
    rw.writeInt(res.size()); //количество взятых камней
    rw.writeVector(res); //сами камни

    delete[] arr;
    return 0;
}