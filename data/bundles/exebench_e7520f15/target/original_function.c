static const int CalcOffsetAndShift(const int x, const int y, size_t *offset, size_t *shift)
{
 if ((x < 0) || (x >= 84) || (y < 0) || (y >= 48))
    {
        return -1;
    }
    if ((offset == NULL) || (shift == NULL))
    {
        return -1;
    }

    *offset = x + ((int)(y / 8))*84;
    *shift = y % 8;

    return 0;
}