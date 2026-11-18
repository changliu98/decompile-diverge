int SDL_imageFilterAddByteToHalfMMX(unsigned char *Src1, unsigned char *Dest, int SrcLength, unsigned char C, unsigned char *Mask)
{
    int i;
    int istart;
    int iend;
    int Result;
    __m64 *isrc;
    __m64 *idst;
    __m64 *imask;
    __m64 *ialpha;
    __m64 ialphaval;
    __m64 itemp;
    __m64 izero;


    if ((SrcLength & 7) != 0) {
        return(-1);
    }


    if ((C == 0) || (Mask == NULL)) {
        return(-1);
    }


    isrc = (__m64 *) Src1;
    idst = (__m64 *) Dest;
    imask = (__m64 *) Mask;


    istart = 0;
    iend = SrcLength;


    itemp = *imask;
    itemp = _mm_unpacklo_pi8(itemp, itemp);
    itemp = _mm_unpacklo_pi8(itemp, itemp);
    itemp = _mm_unpacklo_pi8(itemp, itemp);
    itemp = _mm_unpacklo_pi8(itemp, itemp);
    imask = &itemp;


    ialphaval = _mm_set1_pi8(C);
    ialpha = (__m64 *) &ialphaval;


    izero = _mm_setzero_si64();


    for (i = istart; i < iend; i += 8) {
        itemp = *isrc;
        itemp = _mm_unpacklo_pi8(itemp, izero);
        itemp = _mm_maddubs_epi16(itemp, *imask);
        itemp = _mm_adds_epu16(itemp, *ialpha);
        itemp = _mm_packus_epi16(itemp, itemp);
        *idst = _mm_srli_pi16(*idst, 8);
        *idst = _mm_or_si64(*idst, itemp);

        isrc++;
        idst++;
        imask++;
    }


    _mm_empty();


    Result = (i - istart);

    return(Result);
}