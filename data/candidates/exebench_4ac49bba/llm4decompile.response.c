int SDL_imageFilterAddUintMMX(unsigned char *Src1, unsigned char *Dest, int SrcLength, unsigned int C, unsigned int D)
{
    int i;
    unsigned int *iSrc1 = (unsigned int *)Src1;
    unsigned int *iDest = (unsigned int *)Dest;
    unsigned int *iC = (unsigned int *)&C;
    unsigned int *iD = (unsigned int *)&D;

    __asm__ __volatile__ (
     "movd %1, %%mm1\n"
     "movd %2, %%mm2\n"
     "punpcklbw %%mm1, %%mm1\n"
     "punpcklbw %%mm2, %%mm2\n"
     "paddw %%mm1, %%mm2\n"
     "packuswb %%mm2, %%mm2\n"
     "movd %%mm2, %0\n"
    : "=m"(i)
    : "m"(iSrc1), "m"(iC)
    : "%mm1", "%mm2"
    );

    return(-1);
}