#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void findTracks(long n, long m, long k, long *ans) {
    for (int i = 0; i < m; i++)
        ans[i] = 1;

    k--;

    for (long i = m - 1; i >= 0 && k > 0; i--) {
        ans[i] = k % n + 1;
        k /= n;
    }
}

string solve(long n, long m, long k) {
    long *ans = new long[m];
    findTracks(n, m, k, ans);

    stringstream ss;
    for (int i = 0; i < m - 1; ++i)
        ss << ans[i] << " ";

    ss << ans[m - 1];

    delete[] ans;
    return ss.str();
}

int main() {
    long m, n, k;
    fstream fin;
    fstream fout;

    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);

    if (fin.is_open()) {
        fin >> n;
        fin >> m;
        fin >> k;

        fout << solve(n, m, k) << endl;

        fout.close();
        fin.close();
    }

    return 0;
}