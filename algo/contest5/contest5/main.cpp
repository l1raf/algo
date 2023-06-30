#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Основная задача - реализовать данный метод
//Результат поместить в переменную res, она как раз доступна для изменения
//Можно добавлять любое количество любых вспомогательных методов, структур и классов
void getBorders(string& s, string& res) {
    int n = s.length();
    int* br = new int[n];
    br[0] = 0;

    int currentLen;
    for (int i = 1; i < n; i++) {
        currentLen = br[i - 1];

        while ((currentLen > 0) && (s[i] != s[currentLen]))
            currentLen = br[currentLen - 1];

        if (s[i] == s[currentLen])
            br[i] = currentLen + 1;
        else
            br[i] = 0;
    }

    int index = n - 1;
    while (br[index] > 0) {
        res = '\n' + s.substr(0, br[index]) + res;
        cout << s.substr(0, br[index]) << '\n';
        index = br[index] - 1;
    }

    res = res.substr(1, res.length() - 1);

    delete[] br;
}

//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main() {
    string input;
    string res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open()) {
        getline(fin, input);
        fin.close();
    }

    getBorders(input, res);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}
