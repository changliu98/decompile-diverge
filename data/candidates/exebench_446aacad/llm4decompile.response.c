int cond_read_lock(cond_lock_t *lk)
{
 if (lk->readers < 0)
  return 0;
 lk->readers++;
 return 1;
}