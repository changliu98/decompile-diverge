double drand48(long *seed)
{
  long a = 15485863ull;
  long c = 1ull;
  long mask = 0xfff;
  long seed0 = *seed & mask;
  long seed1 = (*seed >> 12) & mask;
  long seed2 = (*seed >> 24) & mask;
  long newseed0 = (seed0 * a) & mask;
  long newseed1 = (seed1 * a) & mask;
  long newseed2 = (seed2 * a) & mask;
  long sum = (newseed0 + newseed1 * 1024 + newseed2 * 1024 * 1024);
  newseed0 = (sum & mask);
  newseed1 = (sum >> 12) & mask;
  newseed2 = (sum >> (12 * 2)) & mask;
  *seed = (newseed0 | (newseed1 << 12) | (newseed2 << (12 * 2)));
  return (double) (newseed0 * 0.000244140625 + newseed1 * 0.000244140625 + newseed2 * 0.00390625);
}