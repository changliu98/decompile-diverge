int SDL_imageFilterShiftLeftUintMMX(unsigned char *Src1, unsigned char *Dest, unsigned int SrcLength, unsigned char N)
{
    int i;
    int istart;
    unsigned char *cursrc1;
    unsigned char *curdest;
    int result;


    if ((N > 7) || (N < 0)) {
        return (-1);
    }

    if ((SrcLength % 8) != 0) {
        return (-1);
    }


    __asm__ __volatile__ (
        "movd %1, %%mm7\n"
        "pxor %%mm6, %%mm6\n"
        "punpcklbw %%mm6, %%mm7\n"
        "movq %%mm7, %%mm6\n"
        "punpcklwd %%mm6, %%mm7\n"
        "movq %%mm7, %%mm6\n"
        "punpckldq %%mm6, %%mm7\n"
        : "=m" (result)
        : "m" (N)
    );


    cursrc1 = Src1;
    curdest = Dest;
    istart = SrcLength / 8;

    __asm__ __volatile__ (
        "movq (%0), %%mm0\n"
        "movq 8(%0), %%mm1\n"
        "movq 16(%0), %%mm2\n"
        "movq 24(%0), %%mm3\n"
        "movq 32(%0), %%mm4\n"
        "movq 40(%0), %%mm5\n"
        "movq 48(%0), %%mm6\n"
        "movq 56(%0), %%mm7\n"
        "psllw %%mm7, %%mm0\n"
        "psllw %%mm7, %%mm1\n"
        "psllw %%mm7, %%mm2\n"
        "psllw %%mm7, %%mm3\n"
        "psllw %%mm7, %%mm4\n"
        "psllw %%mm7, %%mm5\n"
        "psllw %%mm7, %%mm6\n"
        "psllw %%mm7, %%mm7\n"
        "movq %%mm0, (%1)\n"
        "movq %%mm1, 8(%1)\n"
        "movq %%mm2, 16(%1)\n"
        "movq %%mm3, 24(%1)\n"
        "movq %%mm4, 32(%1)\n"
        "movq %%mm5, 40(%1)\n"
        "movq %%mm6, 48(%1)\n"
        "movq %%mm7, 56(%1)\n"
        :
        : "r" (cursrc1), "r" (curdest)
    );


    for (i = istart; i < SrcLength; i += 8) {
        __asm__ __volatile__ (
            "movq (%0), %%mm0\n"
            "movq 8(%0), %%mm1\n"
            "movq 16(%0), %%mm2\n"
            "movq 24(%0), %%mm3\n"
            "movq 32(%0), %%mm4\n"
            "movq 40(%0), %%mm5\n"
            "movq 48(%0), %%mm6\n"
            "movq 56(%0), %%mm7\n"
            "psllw %%mm7, %%mm0\n"
            "psllw %%mm7, %%mm1\n"
            "psllw %%mm7, %%mm2\n"
            "psllw %%mm7, %%mm3\n"
            "psllw %%mm7, %%mm4\n"
            "psllw %%mm7, %%mm5\n"
            "psllw %%mm7, %%mm6\n"
            "psllw %%mm7, %%mm7\n"
            "movq %%mm0, (%1)\n"
            "movq %%mm1, 8(%1)\n"
            "movq %%mm2, 16(%1)\n"
            "movq %%mm3, 24(%1)\n"
            "movq %%mm4, 32(%1)\n"
            "movq %%mm5, 40(%1)\n"
            "movq %%mm6, 48(%1)\n"
            "movq %%mm7, 56(%1)\n"
            :
            : "r" (cursrc1), "r" (curdest)
        );

        cursrc1 += 8;
        curdest += 8;
    }


    __asm__ __volatile__ (
        "emms\n"
    );

    return (0);
}