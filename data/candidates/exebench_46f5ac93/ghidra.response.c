void spin_unlock(int *lock)

{
  int *lock_local;
  
  *(undefined1 *)lock = 0;
  return;
}