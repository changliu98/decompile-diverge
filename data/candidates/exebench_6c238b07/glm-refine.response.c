int __cdecl genx(unsigned __int8 *dst, const unsigned __int8 *field)
{
    short index[256];
    int error = 0;

    // Initialize the index array with -1.
    // Note: 'short' is used instead of 'int' to match the original stack footprint.
    for (int i = 0; i < 256; ++i)
        index[i] = -1;

    // Build an inverse mapping of the 'field' array.
    // If a duplicate value is encountered, set the error flag.
    for (int i = 0; i < 256; ++i)
    {
        if (index[field[i]] == -1)
            index[field[i]] = i;
        else
            error = 1;
    }

    // Write the inverse mapping to the destination buffer.
    // Values are sign-extended from 'short' to 'unsigned __int8' (truncated to 8 bits).
    for (int i = 0; i < 256; ++i)
        dst[i] = (unsigned __int8)index[i];

    return error ? -1 : 0;
}