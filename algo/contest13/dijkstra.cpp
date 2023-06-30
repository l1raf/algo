#include "ReadWriter.h"
#include <queue>

using namespace std;

void dijkstra(int src, int n, vector<vector<pair<int, int>>> &adj, int *distance) {
    for (int i = 0; i < n; i++)
        distance[i] = 30001;

    distance[src] = 0;

    priority_queue<pair<int, int>> q;
    q.push(make_pair(0, src));

    while (!q.empty()) {
        int v = q.top().second;
        int w = -q.top().first;
        q.pop();

        if (w <= distance[v]) {
            for (int i = 0; i < adj[v].size(); i++) {
                int to = adj[v][i].first;
                int len = adj[v][i].second;

                if (distance[v] + len < distance[to]) {
                    distance[to] = distance[v] + len;
                    q.push(make_pair(-distance[to], to));
                }
            }
        }
    }
}

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ориентированных ребер, каждое ребро представлено 3-мя числами (А, В, W),
// где A и B - номера вершин, которые оно соединяет (Путь строго из А в В), и W - вес ребра
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора кратчайших расстояний из 0-й вершины во все остальные начиная с 1-й, то есть N-1 значение должно быть
void solve(int N, int M, vector<Edge> &edges, vector<int> &result) {
    int *distance = new int[N];
    vector<vector<pair<int, int>>> adj(N);

    for (Edge &edge : edges)
        adj[edge.A].push_back(make_pair(edge.B, edge.W));

    dijkstra(0, N, adj, distance);

    for (int i = 1; i < N; ++i)
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
    rw.writeInt(result.size());
    rw.writeIntValues(result);

    return 0;
}