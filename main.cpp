//
// Created by pwlqr on 11/07/2022.
//
#include "DataBase.h"
#include <iostream>
#include <cstring>
#include <map>

using namespace std;

bool isState(char *str);

bool isOperation(char *str);

int main(int argc, char **argv) {

    if (argc < 2) {
        cout << "less arguments then expected!" << endl;
        return 1;
    }

    //cout << "cube " << argv[1] << " is maintained." << endl;

    if (argv[2] == NULL || isOperation(argv[2])) {
        switch (DataBase::maintainObject(argv[1], argv[2])) {
            case ERROR: {
                cout << "Error!!" << endl;
                return 1;
            }
            case SUCCESS: {
                //do nothing, the output is already out.
            }
                break;
            case CREATED: {
                DataBase::maintainObject(argv[1], argv[2]);
            }
        }
    } else if (isState(argv[2])) {
        DataBase::writeState(argv[1], argv[2]);
        cout << argv[2] << endl;
    } else {
        cout << "ERROR!!" << endl;
        return 1;
    }

    return 0;
}


bool isState(char *str) {

    if (strlen(str) != 53) return false;

    map<char, int> counter;
    counter['y'] = 0;
    counter['g'] = 0;
    counter['r'] = 0;
    counter['w'] = 0;
    counter['o'] = 0;
    counter['b'] = 0;
    counter['.'] = 0;

    for (int i = 0; i < strlen(str); ++i) {
        ++counter[str[i]];
    }

    return counter['y'] == 8 && counter['g'] == 8 && counter['r'] == 8 && counter['w'] == 8 && counter['o'] == 8 &&
           counter['b'] == 8 && counter['.'] == 5;

}

bool isOperation(char *str) {
    char options[] = {'r', 'l', 'u', 'd', 'f', 'b'};
    bool flag;
    for (int i = 0; i < strlen(str); ++i) {
        flag = false;
        for (int j = 0; j < 6; ++j) {
            if (str[i] == options[j])
                flag = true;
        }
        if (!flag)return false;
    }
    return true;
}







