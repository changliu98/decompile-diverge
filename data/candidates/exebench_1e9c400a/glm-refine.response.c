void __cdecl myArrayDiv(const float *src, float divisor, float *result)
{
    // Unrolled for maximum readability, as the array size is fixed at 5
    result[0] = src[0] / divisor;
    result[1] = src[1] / divisor;
    result[2] = src[2] / divisor;
    result[3] = src[3] / divisor;
    result[4] = src[4] / divisor;
}