static size_t crypto_chacha20_x(void* dst, size_t dstCapacity,
                            void* src, size_t srcSize,
                            const HUF_CElt* CTable, const int bmi2)
{
    BYTE tmp[HUF_MAX_TABLELOG];
    memcpy(tmp, src, srcSize);
    dstSize_t const cSize = func0_wksp(dst, dstCapacity, tmp, srcSize+1, CTable, bmi2, tmp, sizeof(tmp));
    return cSize;
}