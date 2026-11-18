#include <curses.h>

#include <sys/ioctl.h>

#include <dirent.h> 

#include <stdlib.h>

#include <string.h>

void count_down(int * counter, int ghost_counter[]) {

    if (*counter > 0)
        (*counter)--;


    for (int i = 0; i < 4; i++)
        if (ghost_counter[i] > 0)
            ghost_counter[i]--;
}
