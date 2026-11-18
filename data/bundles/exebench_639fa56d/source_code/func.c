#include <stdio.h>

#include <stdlib.h>

void advance_m2pos(int *m2pos){
     *m2pos = (*m2pos + 1)%37;
}
