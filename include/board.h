#ifndef BOARD_H
#define BOARD_H

#include "globals.h"

class Board 
{
    public:
        Board();
        ~Board();

        // ai/utils
        static inline char getCell(const char *gs, int r, int c) {
            if (r < 0 || r >= g_board_size || c < 0 || c >= g_board_size) return -1;
            return gs[g_board_size * r + c];
        }

        static inline bool setCell(char *gs, int r, int c, char value) {
            if (r < 0 || r >= g_board_size || c < 0 || c >= g_board_size) return false;
            gs[g_board_size * r + c] = value;
            return true;
        }

        static bool remoteCell(const char *gs, int r, int c);

        static void display(const char *gs);

        // display the board whith alphabetic rows
        static void display2(const char *gs);
};

#endif