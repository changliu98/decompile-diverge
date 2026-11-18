void clib_mallinfo(long *arena,long *hblkhd,long *usmblks,long *fsmblks,long *uordblks,
                  long *fordblks)

{
  long *fordblks_local;
  long *uordblks_local;
  long *fsmblks_local;
  long *usmblks_local;
  long *hblkhd_local;
  long *arena_local;
  
  *arena = -1;
  *hblkhd = -1;
  *usmblks = -1;
  *fsmblks = -1;
  *uordblks = -1;
  *fordblks = -1;
  return;
}