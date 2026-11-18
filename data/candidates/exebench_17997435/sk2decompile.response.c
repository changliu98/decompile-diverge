int trylock(volatile char *lock) {
  char old;
  old = *lock;
  *lock = 1;
  return !old;
}