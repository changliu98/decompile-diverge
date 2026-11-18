void toup(char *chr_ptr)

{
  uchar upcas_diff;
  char *chr_ptr_local;
  
  if (('`' < *chr_ptr) && (*chr_ptr < '{')) {
    *chr_ptr = *chr_ptr + -0x20;
  }
  return;
}