#include <string.h>

char * strcpy(char *pDestination, const char *pSource)
{
    char *pSaveDest = pDestination;

    for(; (*pDestination = *pSource) != 0; ++pSource, ++pDestination);
    return pSaveDest;
}
