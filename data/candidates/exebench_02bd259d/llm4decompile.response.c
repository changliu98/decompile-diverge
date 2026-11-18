int SDL_imageFilterClipToRangeMMX(unsigned char *Src1, unsigned char *Dest, int SrcLength, unsigned char Tmin, unsigned char Tmax)
{
    int i;
    int istart;
    int iend;
    int Result;
    __m64 mm_Tmin;
    __m64 mm_Tmax;
    __m64 mm_Src;
    __m64 mm_Result;


    if ((SrcLength % 8) != 0) {
        return(-1);
    }


    mm_Tmin = SDL_imageMMX_unpack_16_8(Tmin);
    mm_Tmax = SDL_imageMMX_unpack_16_8(Tmax);


    istart = 0;
    iend = SrcLength - 7;


    for (i = istart; i < iend; i += 8) {

        mm_Src = *((__m64 *) (Src1 + i));


        mm_Result = SDL_imageMMX_clipToRange(mm_Src, mm_Tmin, mm_Tmax);


        *((__m64 *) (Dest + i)) = mm_Result;
    }


    Result = SDL_imageFilterClipToRange(Src1 + i, Dest + i, SrcLength - i, Tmin, Tmax);


    _mm_empty();
    _mm_empty();
    _mm_empty();
    _mm_empty();


    return(Result);
}