#include "ReadWriter.h"
#include <queue>

using namespace std;

struct Vertex {
    int parent;
    int key;
};

int getMinKeyVertexIndex(Vertex *vertices, const bool *mst, int n) {
    int min = 30001;
    int index;

    for (int i = 0; i < n; i++) {
        if (!mst[i] && vertices[i].key < min) {
            min = vertices[i].key;
            index = i;
        }
    }

    return index;
}

void primMST(int n, int m, vector<Edge> &edges, vector<Edge> &result, int startEdge) {
    auto *vertices = new Vertex[n];
    auto *mst = new bool[n]{false};

    for (int i = 0; i < n; i++)
        vertices[i].key = 30001;

    int **adj = new int *[n];

    for (int i = 0; i < n; i++)
        adj[i] = new int[n]{0};

    for (Edge &edge : edges) {
        adj[edge.A][edge.B] = edge.W;
        adj[edge.B][edge.A] = edge.W;
    }

    vertices[startEdge].key = 0;
    vertices[startEdge].parent = -1;

    for (int i = 0; i < n - 1; i++) {
        int u = getMinKeyVertexIndex(vertices, mst, n);

        mst[u] = true;

        for (int v = 0; v < n; v++) {
            if (adj[u][v] && !mst[v] && adj[u][v] < vertices[v].key) {
                vertices[v].parent = u;
                vertices[v].key = adj[u][v];
            }
        }
    }

    for (Edge &edge : edges)
        if (vertices[edge.B].parent == edge.A || vertices[edge.A].parent == edge.B)
            result.push_back(edge);

    for (int i = 0; i < n; i++)
        delete[] adj[i];

    delete[] adj;
    delete[] vertices;
    delete[] mst;
}

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ребер, каждое ребро представлено 3-мя числами (А,В,W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра,
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора ребер, передается по ссылке (&), чтобы не копировать его.
void solve(int N, int M, vector<Edge> &edges, vector<Edge> &result) {
    primMST(N, M, edges, result, 0);
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