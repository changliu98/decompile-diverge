int __cdecl cond_read_lock(int *lock)
{
  // If the lock is held by a writer (indicated by a negative value),
  // the read lock cannot be acquired.
  if (*lock < 0)
    return 0;

  // Increment the reader count
  (*lock)++;

  // Successfully acquired the read lock
  return 1;
}