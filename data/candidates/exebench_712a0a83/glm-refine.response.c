void __cdecl advance_m1pos(int *m1pos)
{
    // Advance the position by 1, wrapping around at 61.
    // This is typical of a circular buffer or ring buffer of size 61.
    *m1pos = (*m1pos + 1) % 61;
}