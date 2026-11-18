void __cdecl clib_mallinfo(long *arena, long *hblkhd, long *usmblks, long *fsmblks, long *uordblks, long *fordblks)
{
  *arena = -1LL;
  *hblkhd = -1LL;
  *usmblks = -1LL;
  *fsmblks = -1LL;
  *uordblks = -1LL;
  *fordblks = -1LL;
}