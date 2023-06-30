#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

static void generatePermutations(int N, int t, bool *used, int *permutations, int k, int m) {
    static int num = 0;

    for (int i = 0; i < N; i++) {
        if (num == k)
            return;

        if (!used[i]) {
            used[i] = true;
            permutations[t] = i + 1;

            if (t + 1 < m)
                generatePermutations(N, t + 1, used, permutations, k, m);
            else if (++num == k)
                return;

            used[i] = false;
        }
    }
}

static string get(int N, int k, int m) {
    bool *used = new bool[N]{false};
    int *permutations = new int[N];

    generatePermutations(N, 0, used, permutations, k, m);

    stringstream ss;
    for (int i = 0; i < m - 1; i++)
        ss << permutations[i] << " ";
    ss << permutations[m - 1];

    delete[] permutations;
    delete[] used;

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