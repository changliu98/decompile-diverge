int SDL_imageFilterShiftLeftMMX(unsigned char *Src1, unsigned char *Dest, int SrcLength, unsigned char N)
{
    int i;
    int istart;
    int iend;
    int iinc;
    __m64 m_original;
    __m64 m_result;
    __m64 m_zero;
    __m64 m_twentyfour;


    if ((N > 24) || (N < 0)) {
        return(-1);
    }


    if ((Src1 == NULL) || (Dest == NULL)) {
        return(-1);
    }


    if (SrcLength < 1) {
        return(-1);
    }


    if (Src1 == Dest) {
        return(-1);
    }


    istart = 0;
    iend = SrcLength - 1;
    iinc = 1;


    m_twentyfour = _mm_set_pi8(0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0);
    m_zero = _mm_set_pi8(0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0);


    for (i = istart; i <= iend; i += iinc) {
        m_original = _mm_set_pi8(0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0,
                                 Src1[i], Src1[i + 1], Src1[i + 2], Src1[i + 3], Src1[i + 4], Src1[i + 5], Src1[i + 6], Src1[i + 7]);
        m_result = _mm_sll_pi8(m_original, m_twentyfour);
        m_result = _mm_sub_pi8(m_result, m_zero);
        _mm_storel_pi8(&Dest[i], m_result);
    }


    _mm_empty();
    _mm_sfence();


    return(0);
}