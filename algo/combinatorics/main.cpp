#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

static void C(int n, int m, int *c) {
    int i = m - 1;
    int k = n;

    while (c[i] >= k-- && i > 0)
        i--;

    c[i]++;

    for (int j = i + 1; j < m; ++j)
        c[j] = c[j - 1] + 1;
}

static string get(int N, int k, int m) {
    int *c = new int[m];

    for (int i = 0; i < m; i++)
        c[i] = i + 1;

    for (int i = 0; i < k - 1; i++)
        C(N, m, c);

    stringstream ss;
    for (int i = 0; i < m - 1; i++)
        ss << c[i] << " ";
    ss << c[m - 1];

    delete[] c;

    return ss.str();
}

int main(int argc, const char *argv[]) {
    int M, N, K;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open()) {
        string str;
        getline(fin, str);
        N = atoi(str.c_str());
        getline(fin, str);
        K = atoi(str.c_str());
        getline(fin, str);
        M = atoi(str.c_str());
        fout << get(N, K, M) << endl;

        fout.close();
        fin.close();
    }
    return 0;
}