int SDL_imageFilterSubUintMMX(unsigned char *Src1, unsigned char *Dest, int SrcLength, unsigned int C, unsigned int D)
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
     "punpcklwd %%mm1, %%mm1\n"
     "punpcklwd %%mm2, %%mm2\n"
     "movq %%mm1, %%mm4\n"
     "movq %%mm2, %%mm5\n"
     "punpckldq %%mm1, %%mm1\n"
     "punpckldq %%mm2, %%mm2\n"
     "movq %%mm1, %%mm6\n"
     "movq %%mm2, %%mm7\n"
     :
     : "m" (Src1), "m" (iC), "m" (iD)
     : "%mm1", "%mm2", "%mm3", "%mm4", "%mm5", "%mm6", "%mm7", "memory"
    );

    for (i = 0; i < SrcLength; i += 4)
    {
 __asm__ __volatile__ (
  "movq %0, %%mm0\n"
  "psubw %%mm1, %%mm0\n"
  "psubw %%mm2, %%mm0\n"
  "psubw %%mm3, %%mm0\n"
  "psubw %%mm4, %%mm0\n"
  "psubw %%mm5, %%mm0\n"
  "psubw %%mm6, %%mm0\n"
  "psubw %%mm7, %%mm0\n"
  "movq %%mm0, %1\n"
  :
  : "m" (iSrc1[0]), "m" (iDest[0])
  : "%mm0", "memory"
 );

 iSrc1++;
 iDest++;
    }

    return(-1);
}