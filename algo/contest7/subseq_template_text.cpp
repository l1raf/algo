#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string getLCS(string x, string y, int **l, int i, int j) {
    if (l[i][j] == 0)
        return "";

    if (x[i - 1] == y[j - 1]) {
        return getLCS(x, y, l, i - 1, j - 1) + x[i - 1];
    } else {
        if (l[i - 1][j] < l[i][j - 1])
            return getLCS(x, y, l, i, j - 1);
        else
            return getLCS(x, y, l, i - 1, j);
    }
}

string getLCS(string x, string y) {
    int n = x.length() + 1;
    int m = y.length() + 1;

    int **l = new int *[n];

    for (int i = 0; i < n; i++)
        l[i] = new int[m]{0};

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (x[i - 1] == y[j - 1]) {
                l[i][j] = l[i - 1][j - 1] + 1;
            } else {
                l[i][j] = max(l[i - 1][j], l[i][j - 1]);
            }
        }
    }

    string res = getLCS(x, y, l, n - 1, m - 1);

    for (int i = 0; i < n; i++)
        delete[] l[i];
    delete[] l;

    return res;
}

int main() {
    string x;
    string y;
    string res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open()) {
        getline(fin, x);
        getline(fin, y);
        fin.close();
    }

    res = getLCS(x, y);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}