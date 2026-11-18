int __cdecl proc_alloc_inum(unsigned int *inum)
{
  if (inum) {
    *inum = 1;
  }
  return 0;
}