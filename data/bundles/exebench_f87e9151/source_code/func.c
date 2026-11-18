#include <math.h>

#include <string.h>

static void NearestNeighbor(
    int *index,

    float *array,
    float value,
    int arlength
){
    int i;
    float bestcrit,crit;

    crit=array[0]-value;
    bestcrit=crit*crit;
    *index=0;
    for (i=1; i<arlength; i++) {
        crit=array[i]-value;
        crit=crit*crit;

        if (crit<bestcrit) {
            bestcrit=crit;
            *index=i;
        }
    }
}
