void get_hash(int hash, float *gx)
{
  *gx = (float)(hash & 7)+1.0f;
  if (hash & 8)
    *gx = -*gx;
}