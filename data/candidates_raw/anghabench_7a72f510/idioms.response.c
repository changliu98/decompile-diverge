static unsigned int fmix(unsigned int h)
{
  return ( (h & 0x55555555) + (h >> 1) +
           ((h & 0x33333333) + (h >> 2)) +
           ((h & 0x0f0f0f0f) + (h >> 4)) +
           ((h & 0x00ff00ff) + (h >> 8)) +
           ((h & 0x0000ffff) + (h >> 16)) );
}