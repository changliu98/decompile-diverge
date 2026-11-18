uint64_t func0(uint64_t n, uint64_t p)
{
 uint64_t result = 1;
 for (uint64_t i = 0; i < n; i++)
  result = (result * 2) % p;
 return result;
}