int get_hashmask(int *size)

{
  int tsize;
  int *size_local;
  
  for (tsize = 1; tsize < *size; tsize = tsize << 1) {
  }
  *size = tsize;
  return tsize + -1;
}