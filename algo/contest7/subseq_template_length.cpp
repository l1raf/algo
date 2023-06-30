#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int getLCS(string x, string y) {
    int n = x.length() + 1;
    int m = y.length() + 1;

    int **l = new int *[n];

    for (int i = 0; i < n; i++)
        l[i] = new int[m]{0};

    if (n == 1 || m == 1)
        return 0;

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (x[i - 1] == y[j - 1]) {
                l[i][j] = l[i - 1][j - 1] + 1;
            } else {
                l[i][j] = max(l[i - 1][j], l[i][j - 1]);
            }
        }
    }

    int res = l[n - 1][m - 1];

    for (int i = 0; i < n; i++)
        delete[] l[i];
    delete[] l;

    return res;
}

int main() {
    string x;
    string y;
    int res;

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
