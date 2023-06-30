#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int last;

string getResultAsString(int *ans, int n) {
    stringstream ss;

    for (int i = 0; i < n; i++)
        ss << ans[i] << " ";
    ss << ans[n] << "\n";

    return ss.str();
}

bool solve(int *a) {
    if (last == 0)
        return false;

    int k = last - 1;

    while (k != 0 && a[k - 1] <= a[k] && a[k] != 12)
        k--;

    if (a[k] == 12)
        k++;

    a[k]++;

    int sum = 0;
    for (int i = k + 1; i < last + 1; i++)
        sum += a[i];

    if (sum == 0)
        return false;

    for (int i = 1; i < sum; i++)
        a[k + i] = 1;

    last = k + sum - 1;

    return true;
}

int main() {
    long n;
    fstream fin;
    fstream fout;

    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);

    if (fin.is_open()) {
        fin >> n;

        int *a = new int[n];

        for (int i = 0; i < n; i++)
            a[i] = 1;

        fout << getResultAsString(a, n - 1);

        last = n - 1;
        while (solve(a))
            fout << getResultAsString(a, last);

        delete[] a;

        fout.close();
        fin.close();
    }

    return 0;
}
