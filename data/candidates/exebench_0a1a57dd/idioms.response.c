void htonf(float *f)
{
  unsigned int *i = (uint32_t *) f;
  htonl(*i);
}