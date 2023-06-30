#include "ReadWriter.h"

using namespace std;

bool compare(const Edge &a, const Edge &b) {
    return a.W < b.W;
}

int getSet(int *parents, int i) {
    if (parents[i] == i)
        return parents[i];

    return getSet(parents, parents[i]);
}

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ребер, каждое ребро представлено 3-мя числами (А,В,W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра,
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора ребер, передается по ссылке (&), чтобы не копировать его.
void solve(int N, int M, vector<Edge>& edges, vector<Edge>& result)
{
    int *parents = new int[N];

    for (int i = 0; i < N; i++)
        parents[i] = i;

    sort(edges.begin(), edges.end(), compare);

    for (auto &edge : edges) {
        int set1 = getSet(parents, edge.A);
        int set2 = getSet(parents, edge.B);

        if (set1 != set2) {
            result.push_back(edge);
            parents[set2] = set1;
        }
    }

    delete[] parents;
}

int main()
{
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