#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void findTracks(long n, long k, long *ans) {
    for (int i = 0; i < n; i++)
        ans[i] = 1;

    k--;

    for (long i = n++ - 1; i >= 0 && k > 0; i--) {
        ans[i] = k % --n + 1;
        k /= n;
    }
}

string solve(long n, long k) {
    long *ans = new long[n];
    findTracks(n, k, ans);

    stringstream ss;
    for (int i = 0; i < n - 1; ++i)
        ss << ans[i] << " ";

    ss << ans[n - 1];

    delete[] ans;
    return ss.str();
}

int main() {
    long n, k;
    fstream fin;
    fstream fout;

    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);

    if (fin.is_open()) {
        fin >> n;
        fin >> k;

        fout << solve(n, k) << endl;

        fout.close();
        fin.close();
    }

    return 0;
}