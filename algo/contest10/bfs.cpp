#include "ReadWriter.cpp"
#include <queue>
#include <iostream>
#include <algorithm>

//Можно добавлять любые методы для решения задачи.

//Задача - реализовать данный метод, решение должно быть в переменной result
void solve(std::vector<Node> &graph, int start, std::vector<std::string> &result) {
    int k = 1;
    int numberOfNeighbours = 0;
    std::vector<std::string> curRes;
    std::queue<Node *> q;
    q.push(&graph[start]);
    graph[start].visited = true;

    while (!q.empty()) {
        Node *current = q.front();
        q.pop();

        curRes.push_back(current->name);
        std::cout << current->name << "\n";

        int x = 0;

        for (Node *n : current->neighbours) {
            if (!n->visited) {
                q.push(n);
                n->visited = true;
                x++;
            }
        }

        numberOfNeighbours += x;

        if (--k == 0) {
            std::sort(curRes.begin(), curRes.end());
            result.insert(std::end(result), std::begin(curRes), std::end(curRes));
            curRes.clear();
            k = numberOfNeighbours;
            numberOfNeighbours = 0;
        }
    }
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
