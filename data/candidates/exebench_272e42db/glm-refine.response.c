void __cdecl decode_mode10_short_delta(int delta, int *dr, int *dg, int *db)
{
    // Extract the 5-bit blue delta and sign-extend it from 5 bits to 32 bits
    *db = (delta & 0x1F);
    if (*db & 0x10) *db |= 0xFFFFFFF0;
    *db *= 2;

    // Extract the 5-bit green delta and sign-extend it from 5 bits to 32 bits
    *dg = (delta & 0x3E0) >> 5;
    if (*dg & 0x10) *dg |= 0xFFFFFFF0;

    // Extract the 5-bit red delta and sign-extend it from 5 bits to 32 bits
    *dr = (delta & 0x7C00) >> 10;
    if (*dr & 0x10) *dr |= 0xFFFFFFF0;
}