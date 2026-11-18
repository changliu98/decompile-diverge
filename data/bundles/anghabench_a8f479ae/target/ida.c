unsigned int __cdecl ice_txd_use_count(unsigned int size)
{
  return ((85 * size) >> 20) + 1;
}