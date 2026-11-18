void convert_human(size_t size,size_t *nsize,char *c)

{
  int p;
  char *c_local;
  size_t *nsize_local;
  size_t size_local;
  
  p = 0;
  for (size_local = size; 0x400 < size_local; size_local = size_local >> 10) {
    p = p + 1;
  }
  switch(p) {
  case 0:
    *c = ' ';
    break;
  case 1:
    *c = 'K';
    break;
  case 2:
    *c = 'M';
    break;
  case 3:
    *c = 'G';
    break;
  case 4:
    *c = 'T';
    break;
  case 5:
    *c = 'P';
  }
  *nsize = size_local;
  return;
}