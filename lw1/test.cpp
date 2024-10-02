#include <cstdlib>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <windows.h>
#include <random>

using namespace std;
string strFin;
int a, b, c;
int start = 1;
int e = 5;
int n;
main()
{
    ifstream fin;
    fin.open("names.txt");

    ofstream fout;
    fout.open("in.txt");

    if (getline(fin, strFin))
    {
        n = stoi(strFin);
    }

    cout << n;
    fout << n;
    for (int i = 0; i < n; i++)
    {
        getline(fin, strFin);
        int a = rand() % (e - start + 1) + start;
        int b = rand() % (e - start + 1) + start;
        int c = rand() % (e - start + 1) + start;
        strFin += ' ' + to_string(a) + ' ' + to_string(b) + ' ' + to_string(c);
        fout << endl;
        for (char j : strFin)
        {
            fout << j;
        }
    }
}
