#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

//Необходимо реализовать метод
//о алгоритме можно прочитать в источниках указанных в программе курса, или на странице курса в ЛМС или в презентациях к семинару.
int Wagner_Fischer(string &s, string &t) {
    int cost;
    int m = s.length();
    int n = t.length();

    int **d = new int *[m + 1];

    for (int i = 0; i <= m; i++)
        d[i] = new int[n + 1];

    for (int i = 0; i <= m; i++)
        d[i][0] = i;

    for (int i = 0; i <= n; i++)
        d[0][i] = i;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i - 1] == t[j - 1])
                cost = 0;
            else
                cost = 1;

            d[i][j] = min(d[i - 1][j] + 1,
                          min(d[i][j - 1] + 1,
                              d[i - 1][j - 1] + cost));
        }
    }

    int res = d[m][n];

    for (int i = 0; i < m + 1; i++)
        delete[] d[i];
    delete[] d;

    return res;
}

//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main(int argc, const char *argv[]) {
    int n;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open()) {
        string N;
        getline(fin, N);
        n = atoi(N.c_str());
        for (int i = 0; i < n; i++) {
            string s;
            string t;
            getline(fin, s);
            getline(fin, t);
            fout << Wagner_Fischer(s, t) << (i == n - 1 ? "" : " ");
        }
        fout.close();
        fin.close();
    }
    return 0;
}