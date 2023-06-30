#include "ReadWriter1.h"

using namespace std;

int findMaxSum(int n, int m, pair<int, int> *items, int **sum) {
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < m + 1; j++) {
            if (items[i - 1].first <= j) {
                sum[i][j] = max(sum[i - 1][j], sum[i - 1][j - items[i - 1].first] + items[i - 1].second);
            } else {
                sum[i][j] = sum[i - 1][j];
            }
        }
    }

    return sum[n][m];
}

void findItems(int n, int w, pair<int, int> *items, vector<pair<int, int>> &res, int **sum) {
    if (sum[n][w] == 0) {
        return;
    } else if (sum[n - 1][w] == sum[n][w]) {
        findItems(n - 1, w, items, res, sum);
    } else {
        res.push_back(items[n - 1]);
        findItems(n - 1, w - items[n - 1].first, items, res, sum);
    }
}

//Задача реализовать этот метод
//param N - количество предметов
//param w - ограничения на вес рюкзака
//param items - массив размера N, с предметами - first = вес, second = стоимость
//param res - вектор результатов (предметы, которые надо взять)
void solve(int n, int w, pair<int, int> *items, vector<pair<int, int>> &res) {
    int **sum = new int *[n + 1];

    for (int i = 0; i < n + 1; i++)
        sum[i] = new int[w + 1]{0};

    findMaxSum(n, w, items, sum);
    findItems(n, w, items, res, sum);

    for (int i = 0; i < n + 1; i++)
        delete[] sum[i];
    delete[] sum;
}

int main(int argc, const char *argv[]) {
    ReadWriter rw;
    int N = rw.readInt(); //количество предметов
    int W = rw.readInt(); //ограничения на вес рюкзака

    //структура массив pair выбрана, так как известно количество и у объекта всего 2 характеристики
    //first = вес(weight), second = стоимость (cost)
    //Можно переложить данные в любую другую удобную струтуру
    //Внимание(!) данные не упорядочены, но можно это сделать если вам требуется
    pair<int, int> *arr = new pair<int, int>[N];
    rw.readArr(arr, N);

    //структура вектор pair выбрана, так как неизвестно количество элементов, и у объекта всего 2 характеристики
    //результат, также first = вес(weight), second = стоимость (cost)
    vector<pair<int, int>> res;
    solve(N, W, arr, res);

    int sumCost = 0, sumWeight = 0;
    for (int i = 0; i < res.size(); i++) {
        sumWeight += res[i].first;
        sumCost += res[i].second;
    }
    //записываем ответ в файл
    rw.writeInt(sumCost);
    rw.writeInt(sumWeight);
    rw.writeInt(res.size());
    rw.writeVector(res);

    delete[] arr;
    return 0;
}