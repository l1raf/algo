#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(const pair<int, string> &p1, const pair<int, string> &p2) {
    return p1.second < p2.second;
}

void DFS(int v, bool *visited, vector<string> &names,
         vector<vector<bool>> &relations, std::vector<std::string> &result) {
    visited[v] = true;
    vector<pair<int, string>> neighbors;

    for (int i = 0; i < relations[v].size(); i++)
        if (relations[v][i])
            neighbors.emplace_back(i, names[i]);

    sort(neighbors.begin(), neighbors.end(), compare);

    for (auto &n : neighbors) {
        int t = n.first;

        if (!visited[t])
            DFS(t, visited, names, relations, result);
    }

    result.push_back(names[v]);
}

vector<pair<int, string>> getVertices(int n, vector<string> &names, vector<vector<bool>> &relations) {
    vector<pair<int, string>> vertices;

    for (int i = 0; i < n; i++) {
        int count = 0;

        for (int j = 0; j < n; j++)
            if (!relations[j][i])
                count++;

        if (count == n)
            vertices.emplace_back(i, names[i]);
    }

    return vertices;
}

vector<string> getList(vector<string> &names, vector<vector<bool>> &relations) {
    int n = names.size();
    bool *visited = new bool[n]{false};
    vector<pair<int, string>> vertices = getVertices(n, names, relations); //истоки
    vector<string> result;

    sort(vertices.begin(), vertices.end(), compare);

    for (auto &v : vertices) {
        int t = v.first;

        if (!visited[t])
            DFS(t, visited, names, relations, result);
    }

    reverse(result.begin(), result.end());

    delete[] visited;

    return result;
}

int main() {
    vector<string> names = vector<string>();
    vector<vector<bool>> relations;
    int startIndex;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open()) {
        string str = "";
        getline(fin, str);

        while (str != "#") {
            names.emplace_back(str.substr(str.find(' ') + 1));
            getline(fin, str);
        }

        relations = vector<vector<bool>>(names.size());

        for (int i = 0; i < names.size(); i++) {
            relations[i] = vector<bool>(names.size());
            for (int j = 0; j < names.size(); j++)
                relations[i][j] = false;
        }

        getline(fin, str);

        while (fin) {
            int a = stoi(str.substr(0, str.find(' '))) - 1;
            int b = stoi(str.substr(str.find(' '))) - 1;
            relations[a][b] = true;
            getline(fin, str);
        }

        fin.close();
    }

    vector<string> res = getList(names, relations);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size(); i++)
        fout << res[i] << "\n";
    fout.close();

    return 0;
}