void htonfloat(float *flt)
{
  unsigned int *uflt = (uint32_t*) flt;
  (*uflt) = (((*uflt) & 0xff000000) >> 24) | (((*uflt) & 0x00ff0000) >> 8) | (((*uflt) & 0x0000ff00) << 8) | (((*uflt) & 0x000000ff) << 24);
}