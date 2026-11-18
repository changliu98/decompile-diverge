int cond_read_lock(int *lock) {
  if (*lock < 0) {
    return 0;
  }
  (*lock)++;
  return 1;
}