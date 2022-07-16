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

#pragma region Date Layer.
private:
    /**
     * reads the state from a given file name, and copies it into the state parameter.
     * @param filename the name of the file.
     * @param state the pointer to the place the state should be in.
     * @return the status indecates whether or not the operation succeed, or not.
     */
    static Status readState(char *filename, char *state);

public:
    /**
     * writs the state to a file from the parameter state.
     * @param filename  the name of the file.
     * @param state  the state to write to the file.
     * @return the status of the operation indicates whether or not the operation succeed or not, and if the file was created.
     */
    static Status writeState(char *filename, const char *state);

    /**
     *the main function of the data layer, the responsible to make all the data managmant work.
     * to read to file run fome checkes, preform the operation and write it back to the file if possible.
     * @param name the name of the function to make to changes on.
     * @param op the operation to make.
     * @return status of the operation, if succeeded or not.
     */
    static Status maintainObject(char *name, char *op);

#pragma endregion


#pragma region the api between layets.
private:
    /**
     * the api function that makes the translation of the command from the data layer to the logical layer.
     * @param state the state to make the change on.
     * @param op the operation to make.
     * @return the status of the operation by the logic later.
     */
    static Status preformAction(char *state, char *op);

#pragma endregion


#pragma region the Logic Layer.
private:
/**
 * represent  a state of a cube to make a changes on.
 */
    class Cube {
    public:
        /**
         * the main function of this layer and its only endpoint for the api of the data layer.
         * @param state the state to make the changes on.
         * @param op  the operation to make.
         * @return 0 if succeeded and 1 if not.
         */
        static int cubeOperation(char *state, char *op);

    private:
        /**
         * the ability to escape the input to this layer.
         * @param op
         * @return not implemented yet. writen for farther extension.
         */
        static char *escapedOperation(char *op);

        /**
         * make use of both the helper functions and performs a complete move of the cube.
         * @param state the state to make the move on.
         * @param side the side on the cube to make the move on.
         * @return
         */
        static int rotateCube(char *state, const int &side) {
            return rotateEdge(state, side) + rotateSide(state, side);
        }

        /**
         * rotate only the side of the cube. the side itself.
         * @param state the state to move.
         * @param side the side move.
         * @return 0 if succeeded, 1 if not.
         */
        static int rotateSide(char *state, const int &side);

        /**
         * moves the edge around the side itself.
         * @param state the state to make the change on.
         * @param side the side to move its edge.
         * @return
         */
        static int rotateEdge(char *state, const int &side);

        /**
         * the dictionary contains all the relation between side and the letter it is represented by.
         * @param move the letter.
         * @return  the side number.
         */
        static int move(const char &move);

        /**
         * helper function that moves three chars form one string to another.
         * @param dst the dst string.
         * @param srcIndex the index to start picking the letters from.
         * @param src the src string.
         * @param dstIndex the index to start pasting to chars on.
         */
        static void copyTreeChars(char *dst, const int &srcIndex, const char *src, const int &dstIndex);

        /**
         * the array that contains for every side of the cubes what sides we need to move and with what index in them we need to start moving the chars.
         * the information represented by the index on the state array to start the moving from.
         */
        static int edgeMovement[6][4];
    };

#pragma endregion

};


#endif //CUBEMANAGMENT_CUBE_H
