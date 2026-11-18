void __cdecl dpaa_set_bits(u64 mask, volatile u64 *p)
{
    *p |= mask;
}