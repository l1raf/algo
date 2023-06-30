#include <iostream>
#include <string>

using namespace std;

bool isValid(int i, int j, int r, string *field) {
    for (int k = 0; k < r; k++) {
        if (!(field[i][j] == field[i - k][j - r + k] &&
            field[i][j] == field[i - r + k][j + k] &&
            field[i][j] == field[i + k][j + r - k] &&
            field[i][j] == field[i + r - k][j - k]))
            return false;
    }

    return true;
}

//int findNumberOfPosters(int n, int m, string *field) {
//    int count = n * m;
//
//    for (int i = 1; i < n; i++) {
//        for (int j = 1; j < m - 1; j++) {
//            int r = 1;
//            while (i + r < n && j + r < m && i - r >= 0 && j - r >= 0) {
//                if (isValid(i, j, r, field)) {
//                    count++;
//                    r++;
//                } else {
//                    break;
//                }
//            }
//        }
//    }
//
//    return count;
//}

void findNumberOfPosters(int n, int m, string *field, int **count) {
    for (int i = 0; i < n; i++) {
        count[i] = new int[m];
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            count[i][j] = 1;

    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < m - 1; j++) {
            if (isValid(i, j, count[i - 1][j], field)) {
                count[i][j] = count[i - 1][j] + 1;
            } else {
                //TODO
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    auto *field = new string[n];
    auto **count = new int *[n];

    for (int i = 0; i < n; i++) {
        cin >> field[i];
    }

    findNumberOfPosters(n, m, field, count);

    int ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans += count[i][j];
            cout << count[i][j] << " ";
        }
        cout << "\n";

        delete[] count[i];
    }

    cout << ans;

    delete[] count;
    delete[] field;

    return 0;
}