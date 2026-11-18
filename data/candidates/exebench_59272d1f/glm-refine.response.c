void __cdecl bo_backoff(int *bwait, int cap)
{
  int current_wait = *bwait;

  // Delay loop: spins 'current_wait' times
  for (int i = current_wait; i; --i)
    ;

  // Exponential backoff with a cap
  *bwait = (2 * current_wait >= cap) ? cap : 2 * current_wait;
}