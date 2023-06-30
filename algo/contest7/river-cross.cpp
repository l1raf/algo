#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Основная задача - реализовать данный метод
int countMaxCross(string &riverMap) {
    //Минимальное количество переправ для левого и правого берегов реки
    int l = 0;
    int r = 1;

    for (char i : riverMap) {
        if (i == 'L') {
            l = min(l + 1, r + 1);
            r = min(r, l + 1);
        } else if (i == 'R') {
            r = min(l + 1, r + 1);
            l = min(l, r + 1);
        } else {
            l = min(l + 1, r + 2);
            r = min(l + 1, r + 1);
        }
    }

    return r;
}


int main() {
    string riverMap;
    int res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open()) {
        getline(fin, riverMap);
        fin.close();
    }

    res = countMaxCross(riverMap);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}
