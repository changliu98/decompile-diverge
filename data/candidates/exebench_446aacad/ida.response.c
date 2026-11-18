int __cdecl cond_read_lock(int *lk)
{
  if ( *lk < 0 )
    return 0;
  ++*lk;
  return 1;
}