#include <iostream>

using namespace std;

long long getNumberOfPaws(int level, long long *values) {
    long long a = 0, b = 1, c;

    if (level < 3)
        return a;

    if (level == 3)
        return b;

    if (values[level])
        return values[level];

    for (int i = 4; i <= level; i++) {
        c = (b + 2 * a) % 1000000007;

        if (i % 3 == 0)
            c++;

        a = b;
        b = c;

        values[i] = c;
    }

    return b % 1000000007;
}

int getMax(const int *arr, int n) {
    int max = -1;

    for (int i = 0; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    return max;
}

int main() {
    int n;
    cin >> n;

    int *trees = new int[n];

    for (int i = 0; i < n; i++)
        cin >> trees[i];

    auto *values = new long long[getMax(trees, n) + 1]{0};

    for (int i = 0; i < n; i++)
        cout << (4 * getNumberOfPaws(trees[i], values)) % 1000000007 << "\n";

    delete[] trees;
    delete[] values;
}