xxh_u32 __cdecl XXH32_round(xxh_u32 acc, xxh_u32 input)
{
  return -1640531535 * __ROL4__(acc - 2048144777 * input, 13);
}