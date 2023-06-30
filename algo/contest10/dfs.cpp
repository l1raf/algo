#include "ReadWriter.cpp"
#include <iostream>
#include <algorithm>

bool compare(Node *n1, Node *n2) {
    return n1->name < n2->name;
}

void DFS(Node *v, std::vector<std::string> &result) {
    v->visited = true;
    result.push_back(v->name);

    std::sort(v->neighbours.begin(), v->neighbours.end(), compare);

    for (auto &n : v->neighbours) {
        if (!n->visited) {
            DFS(n, result);
        }
    }
}

//Задача - реализовать данный метод, решение должно быть в переменной result
void solve(std::vector<Node> &graph, int start, std::vector<std::string> &result) {
    DFS(&graph[start], result);
}

int main() {
    std::vector<Node> graph;
    std::vector<std::string> result;
    int start;

    ReadWriter rw;
    rw.readGraph(graph, start);
    solve(graph, start, result);
    rw.writeAnswer(result);
    return 0;
}
