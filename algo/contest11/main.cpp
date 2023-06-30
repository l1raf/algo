#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <stdlib.h>
#include <algorithm>

using namespace std;

void dfs(vector<string> &vecOfResult, int position, bool *wasChecked, vector<string> &names,
         vector<vector<bool>> &relations) {
    vector<string> name;
    vector<int> index;
    wasChecked[position] = 1;
    for (int j = 0; j < relations[position].size(); j++) {
        if (relations[position][j] == 1) {
            name.push_back(names[j]);
            index.push_back(j);
        }
    }
    for (int i = 0; i < name.size(); i++) {
        for (int j = i + 1; j < index.size(); j++) {
            if (name[i] > name[j]) {
                swap(name[i], name[j]);
                swap(index[i], index[j]);
            }
        }
    }
    for (int j = 0; j < name.size(); j++) {
        if (wasChecked[index[j]] == 0)
            dfs(vecOfResult, index[j], wasChecked, names, relations);
    }
    vecOfResult.push_back(names[position]);
}

vector<string> getList(vector<string> &names, vector<vector<bool>> &relations, vector<string> &parentsName,
                       vector<int> &parentsIndex) {
    int length = names.size();
    bool *wasChecked = new bool[length];
    vector<string> vecOfResult;
    for (int i = 0; i < length; i++)
        wasChecked[i] = 0;
    for (int i = 0; i < parentsName.size(); i++) {
        if (wasChecked[parentsIndex[i]] == 0)
            dfs(vecOfResult, parentsIndex[i], wasChecked, names, relations);
    }
    reverse(vecOfResult.begin(), vecOfResult.end());
    delete[] wasChecked;
    return vecOfResult;
}

int main() {
    vector<string> names = vector<string>();
    vector<vector<bool>> relations;
    vector<string> parentsName;
    vector<int> parentsIndex;
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
        bool *isTrue = new bool[names.size()];
        for (int i = 0; i < names.size(); i++)
            isTrue[i] = false;
        getline(fin, str);
        while (fin) {
            int a = stoi(str.substr(0, str.find(' '))) - 1;
            int b = stoi(str.substr(str.find(' '))) - 1;
            relations[a][b] = true;
            isTrue[b] = true;
            getline(fin, str);
        }
        for (int i = 0; i < names.size(); i++) {
            if (!isTrue[i]) {
                parentsName.push_back(names[i]);
                parentsIndex.push_back(i);
            }
        }
        delete[] isTrue;
        for (int i = 0; i < parentsName.size(); i++) {
            for (int j = i + 1; j < parentsName.size(); j++) {
                if (parentsName[i] > parentsName[j]) {
                    swap(parentsName[i], parentsName[j]);
                    swap(parentsIndex[i], parentsIndex[j]);
                }
            }
        }

        fin.close();
    }

    vector<string> res = getList(names, relations, parentsName, parentsIndex);
    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size(); i++)
        fout << res[i] << "\n";
    fout.close();

    return 0;
}