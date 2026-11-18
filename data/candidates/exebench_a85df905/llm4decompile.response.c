int SDL_imageFilterShiftLeftByteMMX(unsigned char *Src1, unsigned char *Dest, int SrcLength, unsigned char N, unsigned char *Mask)
{
    int i;
    int istart;
    int iend;
    int Result = -1;







    (void)Mask;

    if ((N > 0) && (N < 9)) {







        istart = (N / 8);
        iend = (N % 8);

        if (iend == 0) {
            for (i = 0; i < SrcLength; i++) {
                Dest[i] = Src1[i + istart];
            }
            Result = SrcLength;
        } else {
            unsigned char *psrc1 = &Src1[istart];
            unsigned char *pdest = &Dest[0];
            unsigned char *pmask = &Mask[0];
            __m64 mmx_src1;
            __m64 mmx_dest;
            __m64 mmx_mask;
            __m64 mmx_zero;
            __m64 mmx_reg1;
            __m64 mmx_reg2;






            mmx_zero = _mm_setzero_si64();






            mmx_mask = _mm_unpacklo_epi8(mmx_zero, *(__m64 *) pmask);






            mmx_mask = _mm_unpacklo_epi8(mmx_mask, mmx_zero);






            mmx_mask = _mm_slli_epi16(mmx_mask, (8 - iend));






            for (i = 0; i < (SrcLength - 7); i += 8) {






                mmx_src1 = *(__m64 *) psrc1;






                mmx_dest = _mm_unpacklo_epi8(mmx_src1, mmx_zero);






                mmx_dest = _mm_slli_epi16(mmx_dest, iend);






                mmx_reg1 = _mm_srli_epi16(mmx_src1, (8 - iend));






                mmx_reg2 = _mm_and_si64(mmx_reg1, mmx_mask);






                mmx_dest = _mm_or_si64(mmx_dest, mmx_reg2);






                _mm_storel_epi64((__m128i *) pdest, mmx_dest);






                psrc1 += 8;






                pdest += 8;
            }






            _mm_empty();

            Result = SrcLength;
        }
    }

    return (Result);
}