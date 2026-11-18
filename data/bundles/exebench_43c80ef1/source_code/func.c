#include <assert.h>

#include <stdio.h>

#include <math.h>

#include <string.h>

#include <float.h>

#include <stdlib.h>

static void IndexToData(int * piFace, int * piVert, const int iIndexIn)
{
 piVert[0] = iIndexIn&0x3;
 piFace[0] = iIndexIn>>2;
}
