#include <iostream>

using namespace std;

int findMaxSum(int n, int m, int *w, int *s) {
    int maxSum;
    int **sum = new int *[n + 1];

    for (int i = 0; i < n + 1; i++)
        sum[i] = new int[m + 1]{0};

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < m + 1; j++) {
            if (w[i - 1] <= j) {
                sum[i][j] = max(sum[i - 1][j], sum[i - 1][j - w[i - 1]] + s[i - 1]);
            } else {
                sum[i][j] = sum[i - 1][j];
            }
        }
    }

    maxSum = sum[n][m];

    for (int i = 0; i < n + 1; i++)
        delete[] sum[i];
    delete[] sum;

    return maxSum;
}

int main() {
    int n, m;
    cin >> n >> m;

    int *w = new int[n];
    int *s = new int[n];

    for (int i = 0; i < n; i++)
        cin >> w[i];

    for (int i = 0; i < n; i++)
        cin >> s[i];

    cout << findMaxSum(n, m, w, s);

    delete[] w;
    delete[] s;

    return 0;
}
