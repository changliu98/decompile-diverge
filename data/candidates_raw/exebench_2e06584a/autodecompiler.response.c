long lrand(long *seed, long low, long high)
{
   return ((*seed = (*seed*25013L + 13849L) % (high+1-low) + low));
}