uint32_t incr(uint32_t *addr, uint32_t val)
{
  uint32_t res = *addr;
  *addr += val;
  return res;
}