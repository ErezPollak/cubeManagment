//
// Created by pwlqr on 11/07/2022.
//

#ifndef CUBEMANAGMENT_CUBE_H
#define CUBEMANAGMENT_CUBE_H


#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

enum Status {
    SUCCESS, ERROR, CREATED
};

static const char *DEFAULT_STATE = "yyyyyyyy.rrrrrrrr.bbbbbbbb.oooooooo.gggggggg.wwwwwwww";
static const char *FILE_ENDING = ".cube";

class DataBase {
private:
    static Status readState(char *filename, char *state);


    static Status preformAction(char *state, char *op);

public:
    static Status writeState(char *filename, const char *state);

    static Status maintainObject(char *name, char *op);


private:

    class Cube {
    public:

        static int cubeOperation(char *state, char *op) {
            char *escapedOp = escapedOperation(op);
            for (int i = 0; i < strlen(escapedOp); ++i) {
                rotateCube(state, move(escapedOp[i]));
            }
            return 0;
        }

    private:

        static char *escapedOperation(char *op);

        static int move(const char &move);

        static int rotateCube(char *state, const int &side) {
            return rotateEdge(state, side) + rotateSide(state, side);
        }

        static int rotateSide(char *state, const int &side);

        static int rotateEdge(char *state, const int &side);

        static void copyTreeChars(char *dst, const int &srcIndex, const char *src, const int &dstIndex);

        static int edgeMovement[6][4];
    };
};


#endif //CUBEMANAGMENT_CUBE_H
