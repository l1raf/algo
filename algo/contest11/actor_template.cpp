#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void strongConnect(int v, int *pre, int *trn, bool *onStack, stack<int> &st, vector<string> &names,
                   vector<vector<bool>> &relations, vector<vector<string>> &res, int &index) {
    pre[v] = index;
    trn[v] = index;
    index++;

    st.push(v);
    onStack[v] = true;

    for (int i = 0; i < relations[v].size(); i++) {
        if (relations[v][i]) {
            if (pre[i] == -1) {
                strongConnect(i, pre, trn, onStack, st, names, relations, res, index);
                trn[v] = min(trn[v], trn[i]);
            } else {
                if (onStack[i]) {
                    trn[v] = min(trn[v], pre[i]);
                }
            }
        }
    }

    if (trn[v] == pre[v]) {
        vector<string> currentSCC;

        int w;

        do {
            w = st.top();
            st.pop();
            onStack[w] = false;
            currentSCC.push_back(names[w]);
        } while (w != v);

        sort(currentSCC.begin(), currentSCC.end());
        res.push_back(currentSCC);
    }
}

vector<vector<string>> getList(vector<string> &names, vector<vector<bool>> &relations) {
    int n = names.size();
    vector<vector<string>> res;
    stack<int> st;
    int index = 0;

    int *pre = new int[n];
    int *trn = new int[n];
    bool *onStack = new bool[n]{false};

    for (int i = 0; i < n; i++)
        pre[i] = -1; //undefined

    for (int i = 0; i < n; i++)
        if (pre[i] == -1)
            strongConnect(i, pre, trn, onStack, st, names, relations, res, index);

    sort(res.begin(), res.end());

    delete[] pre;
    delete[] trn;
    delete[] onStack;

    return res;
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

    vector<vector<string>> res = getList(names, relations);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j < res[i].size(); j++)
            fout << res[i][j] << "\n";
        fout << "\n";
    }
    fout.close();

    return 0;
}