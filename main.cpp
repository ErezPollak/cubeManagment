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

/**
 * the main function gets as parameters the name of the cube and ether an operation to make on it or the state for the cube.
 * if the cube exists: it will do on its state the given operations or override it by the new given state.
 * if the cube doesn't exist: it will creat it and do on it the given operation or insert the given state.
 * @param argc the number of parameters inserted into the function
 * @param argv the array of the parameter itself.
 * @return 0 if the process finished properly and 1 if not.
 */
int main(int argc, char **argv) {

    if (argc < 2) {
        cout << "less arguments then expected!" << endl;
        return 1;
    }



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
        cout << "ERROR!!!" << endl;
        return 1;
    }

    return 0;
}

/**
 * the function that determine ether or not the inserted input can represent a state of a cube,
 * by counting the number of appearances of every color and number of sections.
 * @param str the input string.
 * @return true if the string can represent a state of a cube and false if not.
 */
bool isState(char *str) {

    //if the length is not correct the function will return false immediately.
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
        //checks that the points are in the right positions.
        if(i % 9 == 8 && str[i] != '.'){return false;}
        //counting the number of appearances.
        ++counter[str[i]];
    }

    return counter['y'] == 8 && counter['g'] == 8 && counter['r'] == 8 && counter['w'] == 8 && counter['o'] == 8 &&
           counter['b'] == 8 && counter['.'] == 5;

}

/**
 * the function that determines if the str inserted can represent an operation to do on a cube.
 * @param str  the str inserted.
 * @return whether or not the str can represent an operation.
 */
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







