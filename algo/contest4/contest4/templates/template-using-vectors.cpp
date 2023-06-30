#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Необходимо вернуть вектор ans, который содержит три элемента:
// ans[0] - вес найденного самоцвета красного цвета
// ans[1] - вес найденного самоцвета зеленого цвета
// ans[2] - вес найденного самоцвета синего цвета
vector<int> solve(vector<int>& r, vector<int>& g, vector<int>& b)
{
    vector<int> ans(3);

    // Your solution here

    return ans;
}

int main() {
    fstream fin;
    fstream fout;
    fin.open("input.txt",ios::in);
    fout.open("output.txt",ios::out);

    if(fin.is_open()) {
        int t;
        fin >> t;
        while (t--) {
            int nr, ng, nb;
            fin >> nr >> ng >> nb;

            vector<int> r(nr), g(ng), b(nb);
            for (int i = 0; i < nr; ++i)
                fin >> r[i];
            for (int i = 0; i < ng; ++i)
                fin >> g[i];
            for (int i = 0; i < nb; ++i)
                fin >> b[i];

            vector<int> ans = solve(r, g, b);

            fout << ans[0] << ' ' << ans[1] << ' ' << ans[2] << endl;
        }
    }
    fin.close();
    fout.close();
    return 0;
}
