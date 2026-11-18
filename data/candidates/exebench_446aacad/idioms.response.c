int cond_read_lock(int *lk)
{
  if(*lk < 0)
    return 0;
  else
  {
    (*lk)++;
    return 1;
  }
}