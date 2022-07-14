//
// Created by pwlqr on 12/07/2022.
//


#include <iostream>

#include <fstream>

using namespace std;


int main()
{

    string c = "1234";

    ofstream ofile;
    ofile.open("tests.cube", ios::out | ios::binary);
    ofile.write(&c[0] , sizeof(char) * 4);
    ofile.close();

    //char filestr[100];
    char n[sizeof(char) * 4 + 1];

    ifstream ifile;
    ifile.open("tests.cube", ios::in | ios::binary);
    ifile.read(n, sizeof(char) * 4);
    n[sizeof(char) * 4] = '\0';
    cout << n << endl;
    ifile.close();

    return 0;
}
