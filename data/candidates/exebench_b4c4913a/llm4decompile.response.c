int SDL_imageFilterShiftRightUintMMX(unsigned char *Src1, unsigned char *Dest, int SrcLength, unsigned char N)
{
    int i;
    int istart;
    int iend;
    int iinc;
    __m64 m_N;


    if ((N > 31) || (SrcLength < 1)) {
        return(-1);
    }


    SrcLength = (SrcLength / 8) * 8;


    m_N = (__m64) N;


    istart = 8;
    iend = SrcLength;
    iinc = 8;


    for (i = istart; i < iend; i += iinc) {
        __m64 m_Src1 = *((__m64 *) (Src1 + i));
        __m64 m_Dest = *((__m64 *) (Src1 + i - 8));

        m_Dest = m_Dest >> m_N;
        m_Src1 = m_Src1 << (64 - m_N);
        m_Dest = m_Dest | m_Src1;

        *((__m64 *) (Dest + i)) = m_Dest;
    }


    for (i = iend; i < SrcLength + 8; i++) {
        Dest[i] = Src1[i - 8] >> N;
    }


    return(SrcLength);
}