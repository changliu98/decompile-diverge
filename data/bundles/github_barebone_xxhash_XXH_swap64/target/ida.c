xxh_u64 __cdecl XXH_swap64(xxh_u64 x)
{
  return HIBYTE(x) | (x >> 40) & 0xFF00 | (x >> 24) & 0xFF0000 | (x >> 8) & 0xFF000000 | (x << 8) & 0xFF00000000LL | (x << 24) & 0xFF0000000000LL | (x << 40) & 0xFF000000000000LL | (x << 56);
}