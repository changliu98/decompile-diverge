void clib_mallinfo(unsigned long *arena, unsigned long *ordblks,
                   unsigned long *smblks, unsigned long *hblks,
                   unsigned long *hblkhd, unsigned long *usmblks) {
  *arena = -1;
  *ordblks = -1;
  *smblks = -1;
  *hblks = -1;
  *hblkhd = -1;
  *usmblks = -1;
}