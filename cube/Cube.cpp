//
// Created by pwlqr on 12/07/2022.
//

#include "Cube.h"

void cubeOperation(char *state, char *op) {

    if(((string)op).compare("1") == 0) {
        for (int i = 0; i < 5; ++i) {
            state[i] = '*';
        }
    }

    if(((string)op).compare("2") == 0) {
        for (int i = 0; i < 5; ++i) {
            state[i] = '#';
        }
    }

}
