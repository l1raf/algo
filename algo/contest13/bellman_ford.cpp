#include "ReadWriter.h"

using namespace std;

bool bellmanFord(int v, int n, int m, vector<Edge> &edges, int *distance) {
    int i;
    bool any;

    for (i = 0; i < n; i++)
        distance[i] = 30001;

    distance[v] = 0;

    for (i = 0; i < n; i++) {
        any = false;
        for (int j = 0; j < m; j++) {
            if (distance[edges[j].A] < 30001 && distance[edges[j].A] + edges[j].W < distance[edges[j].B]) {
                distance[edges[j].B] = distance[edges[j].A] + edges[j].W;
                any = true;
            }
        }

        if (!any)
            break;
    }

    return (i != n || !any);
}

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ориентированных ребер, каждое ребро представлено 3-мя числами (А, В, W),
// где A и B - номера вершин, которые оно соединяет (Путь строго из А в В), и W - вес ребра
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора кратчайших расстояний из 0-й вершины во все остальные начиная с 1-й, то есть N-1 значение должно быть
void solve(int N, int M, vector<Edge> &edges, vector<int> &result) {
    int *distance = new int[N];

    if (bellmanFord(0, N, M, edges, distance))
        for (int i = 1; i < N; i++)
            result.push_back(distance[i]);

    delete[] distance;
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
    vector<int> result;

    //Алгоритм решения задачи
    solve(N, M, edges, result);

    //Выводим результаты
    if (!result.empty()) {
        rw.writeInt(result.size());
        rw.writeIntValues(result);
    }

    return 0;
}