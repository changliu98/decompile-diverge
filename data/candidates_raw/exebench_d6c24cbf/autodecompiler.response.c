int float_to_int16(float f, int16_t *hi, int16_t *lo, int16_t *sign)
{
    *hi = (int16_t)(f / 256);
    *lo = (int16_t)(f % 256);

    return 2;
}