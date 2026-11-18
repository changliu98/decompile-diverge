int SDL_imageFilterAddMMX(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, int SrcLength)
{
    int i;
    int istart;
    int iend;
    int *iSrc1;
    int *iSrc2;
    int *iDest;


    if ((!MMX_enabled) || (SrcLength & 3)) {
        return (-1);
    }


    iSrc1 = (int *) Src1;
    iSrc2 = (int *) Src2;
    iDest = (int *) Dest;


    istart = ((int) Src1) & 3;
    iend = (SrcLength + istart) & 3;


    for (i = 0; i < istart; i++) {
        *Dest = *Src1 + *Src2;
        Src1++;
        Src2++;
        Dest++;
    }


    __asm__ __volatile__ (
        "movq %0, %%mm0\n"
        "movq %1, %%mm1\n"
        :
        : "m" (iSrc1), "m" (iSrc2)
        : "%mm0", "%mm1"
    );

    __asm__ __volatile__ (
        "paddb %%mm1, %%mm0\n"
        "movq %%mm0, %0\n"
        : "=m" (iDest)
        :
        : "%mm0", "%mm1"
    );


    Src1 += (4 - istart);
    Src2 += (4 - istart);
    Dest += (4 - istart);


    for (i = 0; i < iend; i++) {
        *Dest = *Src1 + *Src2;
        Src1++;
        Src2++;
        Dest++;
    }


    __asm__ __volatile__ (
        "emms\n"
        :
        :
        : "%mm0", "%mm1"
    );

    return (SrcLength);
}