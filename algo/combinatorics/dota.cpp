//
//  main.cpp
//  A
//
//  Created by Данил Нечай on 02.04.2018.
//  Updated by Плесовских Александр on 07.09.2018.
//  Copyright © 2018 Данил Нечай. All rights reserved.
//

#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

static BigInteger FactTree(int n) {
    BigInteger factorial = 1;

    for (int i = 1; i <= n; i++)
        factorial *= i;

    return factorial;
}

static BigInteger C(int n, int k) {
    return FactTree(n) / (FactTree(k) * FactTree(n - k));
}

static BigInteger Pair(int n) {
    BigInteger pairs = 1;

    for (int i = 1; i <= n; i += 2)
        pairs *= i;

    return pairs;
}

int main(int argc, const char *argv[]) {

    int n, N, K;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open()) {
        string str;
        getline(fin, str);
        N = atoi(str.c_str());
        n = N;
        getline(fin, str);
        K = atoi(str.c_str());
        fout << FactTree(N) << endl;
        fout << C(N, K) << endl;
        fout << Pair(N) << endl;
        fout.close();
        fin.close();
    }
    return 0;
}
