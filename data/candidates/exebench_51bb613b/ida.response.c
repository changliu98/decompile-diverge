int __cdecl rand_r(unsigned int *nextp)
{
  *nextp = 1103515245 * *nextp + 12345;
  return HIWORD(*nextp) & 0x7FFF;
}