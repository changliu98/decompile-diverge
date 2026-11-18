int SDL_imageFilterBitAndMMX(unsigned char *Src1, unsigned char *Src2, unsigned char *Dest, int SrcLength)
{
    int i;
    int istart;
    int iend;
    int Result;
    __m64 *imMXSrc1;
    __m64 *imMXSrc2;
    __m64 *imMXDest;
    __m64 imMXTemp;
    __m64 imMXZero;


    (void) Src1;
    (void) Src2;
    (void) Dest;
    (void) SrcLength;

    return (-1);


    if ((Src1 == NULL) || (Src2 == NULL) || (Dest == NULL)) {
        return (-1);
    }

    if (SrcLength <= 0) {
        return (-1);
    }


    imMXSrc1 = (__m64 *) Src1;
    imMXSrc2 = (__m64 *) Src2;
    imMXDest = (__m64 *) Dest;


    istart = (int) imMXSrc1;
    if ((istart & 7) != 0) {
        imMXSrc1 = (__m64 *) ((int) imMXSrc1 & 0xfffffff8);
        imMXSrc2 = (__m64 *) ((int) imMXSrc2 & 0xfffffff8);
        imMXDest = (__m64 *) ((int) imMXDest & 0xfffffff8);

        imMXTemp = *imMXSrc1;
        imMXTemp = _mm_and_si64(imMXTemp, *imMXSrc2);
        *imMXDest = imMXTemp;

        imMXSrc1++;
        imMXSrc2++;
        imMXDest++;

        SrcLength -= 8;
    }


    iend = (SrcLength & 0xfffffff8) + 8;
    for (i = SrcLength; i > 0; i -= 8) {
        imMXTemp = *imMXSrc1;
        imMXTemp = _mm_and_si64(imMXTemp, *imMXSrc2);
        *imMXDest = imMXTemp;

        imMXSrc1++;
        imMXSrc2++;
        imMXDest++;
    }


    imMXZero = _mm_setzero_si64();
    _mm_empty();
    _mm_empty();


    Result = (SrcLength + (istart & 7));

    return (Result);
}