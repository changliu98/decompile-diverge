int SDL_imageFilterShiftRightAndMultByByteMMX(unsigned char *Src1, unsigned char *Dest, int SrcLength, unsigned char N, unsigned char C)
{
    int i;
    int istart;
    int iend;
    int Result;
    __m64 *mSrc1 = (__m64 *) Src1;
    __m64 *mDest = (__m64 *) Dest;
    __m64 mN;
    __m64 mC;


    if ((SrcLength % 8) != 0) {
        return(-1);
    }


    istart = 0;
    iend = SrcLength - 8;


    mN.sb.limit = N;
    mN.sb.offset = 0;
    mN.sb.base = 0;
    mN.sb.high = 0;
    mN.sb.scale = 0;
    mN.sb.index = 0;
    mN.sb.u.s.high = 0;
    mN.sb.u.s.low = N;


    mC.sb.limit = C;
    mC.sb.offset = 0;
    mC.sb.base = 0;
    mC.sb.high = 0;
    mC.sb.scale = 0;
    mC.sb.index = 0;
    mC.sb.u.s.high = 0;
    mC.sb.u.s.low = C;


    for (i = istart; i <= iend; i += 8) {
        Result = (unsigned char) ((((unsigned char) (mSrc1[i].sb.limit)) >> N) * C);
        mDest[i].sb.limit = Result;
        Result = (unsigned char) ((((unsigned char) (mSrc1[i].sb.offset)) >> N) * C);
        mDest[i].sb.offset = Result;
        Result = (unsigned char) ((((unsigned char) (mSrc1[i].sb.base)) >> N) * C);
        mDest[i].sb.base = Result;
        Result = (unsigned char) ((((unsigned char) (mSrc1[i].sb.high)) >> N) * C);
        mDest[i].sb.high = Result;
        Result = (unsigned char) ((((unsigned char) (mSrc1[i].sb.scale)) >> N) * C);
        mDest[i].sb.scale = Result;
        Result = (unsigned char) ((((unsigned char) (mSrc1[i].sb.index)) >> N) * C);
        mDest[i].sb.index = Result;
        Result = (unsigned char) ((((unsigned char) (mSrc1[i].sb.u.s.high)) >> N) * C);
        mDest[i].sb.u.s.high = Result;
        Result = (unsigned char) ((((unsigned char) (mSrc1[i].sb.u.s.low)) >> N) * C);
        mDest[i].sb.u.s.low = Result;
    }


    _mm_empty();
    _mm_sfence();


    return(SrcLength);
}