int func0(int base, int scale)
{
    // Calculate the result by multiplying b by 2 and s, casting to double,
    // then adding b raised to the power of _DAT_00102008 (also cast to double),
    // and finally casting the entire result back to an integer.
    return (int)((double)(base * 2 * scale) + pow((double)base, _DAT_00102008));
}