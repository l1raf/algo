#include "ReadWriter.h"

using namespace std;

void ReadWriter::writeValues(std::vector<std::vector<int>> result) {
    if (!fout.is_open())
        throw std::ios_base::failure("file not open");

    for (int i = 0; i < result.size(); ++i) {
        for (int j = 0; j < result.size(); ++j) {
            if (i != j) {
                if (result[i][j] == 130001)
                    fout << i << " " << j << " " << -1 << "\n";
                else
                    fout << i << " " << j << " " << result[i][j] << "\n";
            }
        }
    }
}

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ориентированных ребер, каждое ребро представлено 3-мя числами (А, В, W),
// где A и B - номера вершин, которые оно соединяет (Путь строго из А в В), и W - вес ребра
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
void solve(int N, int M, vector<Edge> &edges, vector<vector<int>> &result) {
    for (int i = 0; i < N; i++) {
        vector<int> res(N, 130001);
        result[i] = res;
        result[i][i] = 0;
    }

    for (int i = 0; i < M; i++)
        result[edges[i].A][edges[i].B] = edges[i].W;

    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (result[i][j] > result[i][k] + result[k][j] && result[i][k] != 130001 && result[k][j] != 130001)
                    result[i][j] = result[i][k] + result[k][j];
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
    vector<vector<int>> result(N);

    //Алгоритм решения задачи
    solve(N, M, edges, result);
    //Здесь можно вызвать ещё какой-то метод, если вам требуется.

    rw.writeValues(result);

    return 0;
}