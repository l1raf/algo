#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

static void nextPermutation(int n, int *permutations) {
    int i;
    for (i = n - 2; i >= 0; i--)
        if (permutations[i] < permutations[i + 1])
            break;

    int j = n - 1;
    while (permutations[i] >= permutations[j])
        j--;

    swap(permutations[i], permutations[j]);

    int l = i + 1;
    int r = n - 1;

    while (l < r)
        swap(permutations[l++], permutations[r--]);
}

static string get_day(int N, int k) {
    int *permutations = new int[N];

    for (int i = 0; i < N; i++)
        permutations[i] = i + 1;

    for (int i = 1; i < k; i++)
        nextPermutation(N, permutations);

    stringstream ss;
    for (int i = 0; i < N - 1; i++)
        ss << permutations[i] << " ";
    ss << permutations[N - 1];

    delete[] permutations;

    return ss.str();
}

int main(int argc, const char *argv[]) {

    int N, K;
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
        fout << get_day(N, K) << endl;

        fout.close();
        fin.close();
    }

    return 0;
}
