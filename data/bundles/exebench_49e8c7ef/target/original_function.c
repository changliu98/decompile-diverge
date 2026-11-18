void clib_mallinfo
  (long int *arena, long int *hblkhd, long int *usmblks, long int *fsmblks, long int *uordblks, long int *fordblks)
{
# 34 "mallinfo.c"
  *arena = -1.0;
  *hblkhd = -1.0;
  *usmblks = -1.0;
  *fsmblks = -1.0;
  *uordblks = -1.0;
  *fordblks = -1.0;

}