//
// Created by pwlqr on 11/07/2022.
//
#include <cstring>
#include "DataBase.h"


Status DataBase::maintainObject(char *name, char *op) {

    char state[strlen(DEFAULT_STATE) + 1];

    Status readStatus = readState(name, state);
    //in case the file needs to be created in a default mode.
    if (readStatus != SUCCESS) return readStatus;
    // in case of a reading with no operation needed.
    if (op == NULL){ cout << state << endl; return SUCCESS;}

    if (preformAction(state, op) == ERROR) return ERROR;

    cout << state << endl;

    return writeState(name, state);
}

Status DataBase::readState(char *filename, char *str) {
    ifstream file;
    file.open(filename, ios::in | ios::binary);
    if (!file.is_open()) return writeState(filename, DEFAULT_STATE) == SUCCESS ? CREATED : ERROR;
    //file.read(str,strlen(DEFAULT_CUBE) + 1);
    file.getline(str, strlen(DEFAULT_STATE) + 1);
    file.close();
    return SUCCESS;
}

Status DataBase::writeState(char *filename, const char *str) {
    ofstream file;
    file.open(filename, ios::out | ios::binary);
    if (!file.is_open()) return ERROR;
    //file.write(&str,strlen(DEFAULT_CUBE) + 1);
    file << str;
    file.close();
    return SUCCESS;
}


Status DataBase::preformAction(char *state, char *op) {
    return Cube::cubeOperation(state, op) == 0 ? SUCCESS : ERROR;
}



////cube functions//////


int DataBase::Cube::edgeMovement[][4] = {
        {9,  18, 27, 36},
        {4,  42, 45, 20},
        {6,  15, 51, 29},
        {0,  24, 49, 38},
        {2,  33, 47, 11},
        {13, 40, 31, 22}};


int DataBase::Cube::rotateSide(char *state, const int &side) {
    if (side < 0 || side > 6) return 1;

    int initialIndex = side * 9;

    char last[2] = {state[initialIndex + 6], state[initialIndex + 7]};

    for (int i = 4; i > 0; --i) {
        state[i * 2 - 1 + initialIndex] = state[(i - 1) * 2 - 1 + initialIndex];
        state[i * 2 - 1 - 1 + initialIndex] = state[(i - 1) * 2 - 1 - 1 + initialIndex];
    }

    state[initialIndex] = last[0];
    state[initialIndex + 1] = last[1];

    return 0;
}


int DataBase::Cube::rotateEdge(char *state, const int &side) {

    if (side < 0 || side > 6) return 1;

    char temp[3];
    copyTreeChars(temp, 0, state, edgeMovement[side][3]);

    for (int i = 0; i < 3; ++i) {
        //saves for later use the last side coordinates.
        copyTreeChars(state, edgeMovement[side][3 - i], state, edgeMovement[side][3 - i - 1]);
    }

    copyTreeChars(state, edgeMovement[side][0], temp, 0);

    return 0;
}

void DataBase::Cube::copyTreeChars(char *dst, const int &dstIndex, const char *src, const int &srcIndex) {
    int dstFinal, srcFinal;
    for (int i = 0; i < 3; ++i) {
        dstFinal = (dstIndex + i) % 9 != 8 ? dstIndex + i : dstIndex + i - 8;
        srcFinal = (srcIndex + i) % 9 != 8 ? srcIndex + i : srcIndex + i - 8;

        //cout << dstFinal <<"   " << srcFinal << endl;

        dst[dstFinal] = src[srcFinal];
    }
}

int DataBase::Cube::move(const char &move) {
    switch (move) {
        case 'r':
            return 4;
        case 'u' :
            return 0;
        case 'l':
            return 2;
        case 'f':
            return 1;
        case 'b':
            return 3;
        case 'd':
            return 5;
        default:
            return -1;
    }
}

char *DataBase::Cube::escapedOperation(char *op) {
    return op;
}




/*
 *
 *

 ////////////////movments unit tests//////////////////////

C:\Users\pwlqr\Documents\cubeManagment>g++ main.cpp DataBase.cpp -o main.exe

C:\Users\pwlqr\Documents\cubeManagment>main.exe 123 1
cube 123 is maintained.
before : the content is: yyyywwwy.rrrrrrrr.bbgggbbb.oooooooo.bgggggbb.yyywwwww
after  : the content is: yyyywwwy.bggrrrrr.rrrggbbb.bbgooooo.ooogggbb.yyywwwww
action 1 successfully operated!

C:\Users\pwlqr\Documents\cubeManagment>main.exe 123 1
cube 123 is maintained.
file 123 created successfully!

C:\Users\pwlqr\Documents\cubeManagment>main.exe 123 1
cube 123 is maintained.
before : the content is: yyyyyyyy.rrrrrrrr.bbbbbbbb.oooooooo.gggggggg.wwwwwwww
after  : the content is: yyyyyyyy.gggrrrrr.rrrbbbbb.bbbooooo.oooggggg.wwwwwwww
action 1 successfully operated!

C:\Users\pwlqr\Documents\cubeManagment>g++ main.cpp DataBase.cpp -o main.exe

C:\Users\pwlqr\Documents\cubeManagment>main.exe 1
less arguments then expected!
C:\Users\pwlqr\Documents\cubeManagment>main.exe 1
less arguments then expected!
C:\Users\pwlqr\Documents\cubeManagment>main.exe 123 1
cube 123 is maintained.
file 123 created successfully!

C:\Users\pwlqr\Documents\cubeManagment>main.exe 123 1
cube 123 is maintained.
before : the content is: yyyyyyyy.rrrrrrrr.bbbbbbbb.oooooooo.gggggggg.wwwwwwww
after  : the content is: oyyyyyoo.yrrrrryy.bbbbbbbb.oowwwooo.gggggggg.rwwwwwrr
action 1 successfully operated!

C:\Users\pwlqr\Documents\cubeManagment>g++ main.cpp DataBase.cpp -o main.exe

C:\Users\pwlqr\Documents\cubeManagment>main.exe 123 1
cube 123 is maintained.
file 123 created successfully!

C:\Users\pwlqr\Documents\cubeManagment>main.exe 123 1
cube 123 is maintained.
before : the content is: yyyyyyyy.rrrrrrrr.bbbbbbbb.oooooooo.gggggggg.wwwwwwww
after  : the content is: gggyyyyy.rrrrrrrr.ybbbbbyy.oooooooo.ggwwwggg.wwwwbbbw
action 1 successfully operated!

C:\Users\pwlqr\Documents\cubeManagment>g++ main.cpp DataBase.cpp -o main.exe

C:\Users\pwlqr\Documents\cubeManagment>main.exe 123 1
cube 123 is maintained.
file 123 created successfully!

C:\Users\pwlqr\Documents\cubeManagment>main.exe 123 1
cube 123 is maintained.
before : the content is: yyyyyyyy.rrrrrrrr.bbbbbbbb.oooooooo.gggggggg.wwwwwwww
after  : the content is: yyrrryyy.rrwwwrrr.bbbbbbbb.yoooooyy.gggggggg.wwooowww
action 1 successfully operated!

C:\Users\pwlqr\Documents\cubeManagment>g++ main.cpp DataBase.cpp -o main.exe

C:\Users\pwlqr\Documents\cubeManagment>main.exe 123 1
cube 123 is maintained.
file 123 created successfully!

C:\Users\pwlqr\Documents\cubeManagment>main.exe 123 1
cube 123 is maintained.
before : the content is: yyyyyyyy.rrrrrrrr.bbbbbbbb.oooooooo.gggggggg.wwwwwwww
after  : the content is: yyyyyyyy.rrrrbbbr.bbbbooob.oooogggo.ggggrrrg.wwwwwwww
action 1 successfully operated!

 *
 *
 */
