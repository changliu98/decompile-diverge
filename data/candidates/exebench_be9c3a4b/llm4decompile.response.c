int SDL_imageFilterNormalizeLinearMMX(unsigned char *Src1, unsigned char *Dest, int SrcLength, int Cmin, int Cmax, int Nmin, int Nmax)
{
    int i;
    int istart;
    int iend;
    int iinc;
    int normfact;
    int result;
    int mmx_sse_on;

    (void) Src1;
    (void) Dest;
    (void) SrcLength;
    (void) Cmin;
    (void) Cmax;
    (void) Nmin;
    (void) Nmax;
# 1055 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/fgenesis/lv3proj/refs/heads/master/src/shared/SDL_gfx/SDL_imageFilter.c"
    return (-1);


    mmx_sse_on = 0;
# 1070 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/fgenesis/lv3proj/refs/heads/master/src/shared/SDL_gfx/SDL_imageFilter.c"
    if (mmx_sse_on) {
        normfact = (Nmax << 8) - (Nmin << 8);
        if ((Cmax - Cmin) == 0) {
            result = -2;
        } else {
            if (Cmin == 0) {
                istart = 0;
                iend = 128;
                iinc = 1;
            } else {
                istart = (Cmin << 8) / (Cmax - Cmin);
                iend = ((Cmax << 8) / (Cmax - Cmin)) + 1;
                if (iend > 128) {
                    iend = 128;
                }
                iinc = (Cmax << 8) / (Cmin << 8);
            }

            __asm__ __volatile__(
                "movd %1, %%mm7\n"
                "packsswb %0, %%mm7\n"
                "movd %2, %%mm6\n"
                "paddb %3, %%mm7\n"
                "movq %4, %%mm5\n"
                "movq %5, %%mm4\n"
                "movq %%mm7, %%mm3\n"
                "paddb %%mm4, %%mm7\n"
                "psubb %%mm6, %%mm3\n"
                "movq %%mm5, %%mm0\n"
                "paddb %%mm4, %%mm5\n"
                "psubb %%mm6, %%mm1\n"
                "movq %%mm7, (%0)\n"
                "movq %%mm3, 8(%0)\n"
                "movq %%mm5, 16(%0)\n"
                "movq %%mm1, 24(%0)\n"
                :
                : "m" (Dest), "m" (Src1), "m" (Nmin), "m" (normfact), "m" (istart), "m" (iinc)
            );

            for (i = iend; i < 128; i++) {
                Dest[i] = Nmin;
            }

            __asm__ __volatile__("emms\n");
            result = SrcLength;
        }
    } else {

        result = -1;
    }

    return (result);
}