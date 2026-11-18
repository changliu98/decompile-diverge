int trylock(int *lock)

{
  int iVar1;
  char oldval;
  int *lock_local;
  
  LOCK();
  iVar1 = *lock;
  *(undefined1 *)lock = 1;
  UNLOCK();
  return (int)((char)iVar1 == '\0');
}