#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void findSet(int n, int m, int k, int *ans) {
    ans[0] = n;

    if (k == 1)
        return;

    int j = 0;

    for (int i = 0; i < k - 1; i++) {
        if (j == m - 1) {
            j--;

            while (j > 0 && ans[j] == 0)
                j--;

            ans[j++]--;

            if (j != m - 1) {
                ans[j] = ans[m - 1] + 1;
                ans[m - 1] = 0;
            } else {
                ans[j] = ans[m - 1] + 1;
            }
        } else {
            ans[j]--;
            ans[j + 1] = 1;
            j++;
        }
    }
}

string solve(int n, int m, int k) {
    int *ans = new int[m]{0};
    findSet(n, m, k, ans);

    stringstream ss;
    for (int i = 0; i < m - 1; i++)
        ss << ans[i] << " ";

    ss << ans[m - 1];

    delete[] ans;
    return ss.str();
}

int main() {
    int m, n, k;
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
