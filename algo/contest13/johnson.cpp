#include <algorithm>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

class Edge {
public:
    int A;
    int B;
    int W;
    int number;
};

class ReadWriter {
private:

    std::fstream fin;
    std::fstream fout;

public:

    ~ReadWriter() {
        fin.close();
        fout.close();
    }

    ReadWriter() {
        fin.open("input.txt", std::ios::in);
        fout.open("output.txt", std::ios::out);
    }

    // read 2 int value and empty line
    void read2Ints(int &N, int &M) {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        fin >> N >> M;
        //empty line read
        std::string s;
        std::getline(fin, s);
    }

    // read M edges, and fill vector
    void readEgdes(int M, std::vector<Edge> &edges) {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        std::string s;
        for (int i = 0; i < M; i++) {
            Edge e{};
            fin >> e.A >> e.B >> e.W;
            e.number = i;
            edges.push_back(e);
            //empty line read
            std::getline(fin, s);
        }
    }

    // write all values
    void writeValues(std::vector<std::vector<int>> &result) {
        if (!fout.is_open())
            throw std::ios_base::failure("file not open");

        if (!result.empty()) {
            for (int i = 0; i < result.size(); i++) {
                for (int j = 0; j < result.size(); j++) {
                    if (i != j) {
                        if (result[i][j] == 130001)
                            fout << i << " " << j << " " << -1 << "\n";
                        else
                            fout << i << " " << j << " " << result[i][j] << "\n";
                    }
                }
            }
        }
    }
};

bool bellmanFord(int src, int n, int m, vector<Edge> &edges, int *distance) {
    int i;
    bool any;

    for (i = 0; i < n; i++)
        distance[i] = 130001;

    distance[src] = 0;

    for (i = 0; i < n; i++) {
        any = false;
        for (int j = 0; j < m; j++) {
            if (distance[edges[j].A] < 130001 && distance[edges[j].A] + edges[j].W < distance[edges[j].B]) {
                distance[edges[j].B] = distance[edges[j].A] + edges[j].W;
                any = true;
            }
        }

        if (!any)
            break;
    }

    return (i != n || !any);
}

void dijkstra(int src, int n, vector<vector<pair<int, int>>> &adj, int *distance) {
    for (int i = 0; i < n; i++)
        distance[i] = 130001;

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

void addZeroWeightEdges(vector<Edge> &edges, int n) {
    for (int i = 0; i < n; i++) {
        edges[i].A = n;
        edges[i].B = i;
        edges[i].W = 0;
    }
}

void johnson(int n, int m, vector<Edge> &edges, vector<vector<int>> &result) {
    addZeroWeightEdges(edges, n);

    int *bf = new int[n + 1]{0};

    if (!bellmanFord(n, n + 1, n + m, edges, bf)) {
        //есть цикл с отрицательным общим весом
        delete[] bf;
        return;
    }

    for (int i = 0; i < n; i++) {
        vector<int> res(n, 130001);
        result.push_back(res);
    }

    vector<vector<pair<int, int>>> adj(n + 1);

    for (Edge &edge : edges)
        adj[edge.A].emplace_back(edge.B, edge.W);

    for (int i = 0; i < adj.size(); i++)
        for (auto &dest : adj[i])
            dest.second += bf[i] - bf[dest.first];

    for (int i = 0; i < n; i++) {
        int *distance = new int[n + 1]{0};
        dijkstra(i, n + 1, adj, distance);

        for (int j = 0; j < n; j++)
            if (distance[j] != 130001)
                result[i][j] = distance[j] + bf[j] - bf[i];

        delete[] distance;
    }

    delete[] bf;
}

int main() {
    ReadWriter rw;
    //Входные параметры
    //N - количество вершин, M - количество ребер в графе
    int N, M;
    rw.read2Ints(N, M);

    //Вектор ребер, каждое ребро представлено 3-мя числами (А, В, W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра
    //Основной структурой выбран вектор, так как из него проще добавлять и удалять элементы (а такие операции могут понадобиться).
    vector<Edge> edges(N);
    rw.readEgdes(M, edges);

    //Основной структурой для ответа выбран вектор, так как в него проще добавлять новые элементы.
    vector<vector<int>> result;

    //Алгоритм решения задачи
    johnson(N, M, edges, result);
    //Здесь можно вызвать ещё какой-то метод, если вам требуется.

    rw.writeValues(result);

    return 0;
}