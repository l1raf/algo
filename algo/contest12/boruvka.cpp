#include "ReadWriter.h"

using namespace std;

int getComponent(pair<int, int> *trees, int i) {
    if (trees[i].first != i)
        trees[i].first = getComponent(trees, trees[i].first);

    return trees[i].first;
}

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ребер, каждое ребро представлено 3-мя числами (А,В,W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра,
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора ребер, передается по ссылке (&), чтобы не копировать его.
void solve(int N, int M, vector<Edge> &edges, vector<Edge> &result) {
    auto *trees = new pair<int, int>[N];
    auto *cheapestEdges = new int[N];

    for (int i = 0; i < N; i++)
        trees[i] = make_pair(i, 0);

    int count = N;

    while (count > 1) {
        for (int i = 0; i < N; i++)
            cheapestEdges[i] = -1;

        for (int i = 0; i < M; i++) {
            int comp1 = getComponent(trees, edges[i].A);
            int comp2 = getComponent(trees, edges[i].B);

            if (comp1 != comp2) {
                if (cheapestEdges[comp1] == -1 || edges[cheapestEdges[comp1]].W > edges[i].W)
                    cheapestEdges[comp1] = i;

                if (cheapestEdges[comp2] == -1 || edges[cheapestEdges[comp2]].W > edges[i].W)
                    cheapestEdges[comp2] = i;
            }
        }

        //Add edge to MST
        for (int i = 0; i < N; i++) {
            if (cheapestEdges[i] != -1) {
                int comp1 = getComponent(trees, edges[cheapestEdges[i]].A);
                int comp2 = getComponent(trees, edges[cheapestEdges[i]].B);

                comp1 = getComponent(trees, comp1);
                comp2 = getComponent(trees, comp2);

                if (comp1 != comp2) {
                    if (trees[comp1].second < trees[comp2].second) {
                        trees[comp1].first = comp2;
                    } else if (trees[comp1].second > trees[comp2].second) {
                        trees[comp2].first = comp1;
                    } else {
                        trees[comp2].first = comp1;
                        trees[comp1].second++;
                    }

                    result.push_back(edges[cheapestEdges[i]]);
                    count--;
                }
            }
        }
    }

    delete[] trees;
    delete[] cheapestEdges;
}

int main() {
    ReadWriter rw;
    //Входные параметры
    //N - количество вершин, M - количество ребер в графе
    int N, M;
    rw.read2Ints(N, M);

    //Вектор ребер, каждое ребро представлено 3-мя числами (А, В, W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра
    //Основной структурой выбран вектор, так как из него проще добавлять и удалять элементы (а такие операции могут понадобиться).
    vector<Edge> edges;
    rw.readEgdes(M, edges);

    //Основной структурой для ответа выбран вектор, так как в него проще добавлять новые элементы.
    //(а предложенные алгоритмы работают итеративно, увеличивая количество ребер входящих в решение на каждом шаге)
    vector<Edge> result;

    //Алгоритм решения задачи
    //В решение должны входить ребра из первоначального набора!
    solve(N, M, edges, result);

    //Выводим результаты
    rw.writeInt(result.size());
    rw.writeEdges(result);

    return 0;
}