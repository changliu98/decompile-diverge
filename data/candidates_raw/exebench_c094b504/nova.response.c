static void func0(const OPJ_INT32* pSrc, OPJ_INT32* pDst,
                              OPJ_SIZE_T length, OPJ_FLOAT64 mul)
{
    OPJ_FLOAT64 max = 32767.;
    OPJ_FLOAT64 min = -32768.;
    OPJ_FLOAT64 val;

    length = length + length - 1;
    while (length > 0) {
        val = (OPJ_FLOAT64)(*pSrc++) * mul;
        val = val + (OPJ_FLOAT64)(*pSrc++) * mul;
        if (val > max) {
            val = max;
        } else if (val < min) {
            val = min;
        }
        *pDst++ = (OPJ_INT32)val;
        length--;
    }
}