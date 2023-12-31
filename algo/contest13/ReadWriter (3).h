﻿#include "Edge.h"
#include <iostream>
#include <fstream>
#include <vector>

class ReadWriter
{
private:

    std::fstream fin;
    std::fstream fout;

public:

    ~ReadWriter()
    {
        fin.close();
        fout.close();
    }

    ReadWriter()
    {
        fin.open("input.txt", std::ios::in);
        fout.open("output.txt", std::ios::out);
    }

    // read 2 int value and empty line
    void read2Ints(int& N, int& M)
    {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        fin >> N >> M;
        //empty line read
        std::string s;
        std::getline(fin, s);
    }

    // read M edges, and fill vector
    void readEgdes(int M, std::vector<Edge>& edges)
    {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        std::string s;
        for (int i = 0; i < M; i++)
        {
            Edge e;
            fin >> e.A >> e.B >> e.W;
            e.number = i;
            edges.push_back(e);
            //empty line read
            std::getline(fin, s);
        }
    }

    // write int value and empty line
    void writeInt(int K)
    {
        if (!fout.is_open())
            throw std::ios_base::failure("file not open");

        fout << K;
        fout << "\n";         //empty line write
    }

    // write all edges from Vector 
    void writeIntValues(std::vector<int> result)
    {
        if (!fout.is_open())
            throw std::ios_base::failure("file not open");

        for (int i = 0; i < result.size(); i++)
            fout << result[i] << "\n";
    }

};