void __cdecl clib_mallinfo(long *arena, long *hblkhd, long *usmblks, long *fsmblks, long *uordblks, long *fordblks)
{
  *arena     = -1;
  *hblkhd    = -1;
  *usmblks   = -1;
  *fsmblks   = -1;
  *uordblks  = -1;
  *fordblks  = -1;
}