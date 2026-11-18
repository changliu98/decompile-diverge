int __cdecl trylock(volatile int *lock)
{
  char v1; // al

  v1 = *(_BYTE *)lock;
  *(_BYTE *)lock = 1;
  return v1 == 0;
}