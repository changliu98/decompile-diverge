char * read_int(char *s,int nr,int *d)

{
  bool bVar1;
  int result;
  int *d_local;
  int nr_local;
  char *s_local;
  
  result = 0;
  nr_local = nr;
  s_local = s;
  while( true ) {
    nr_local = nr_local + -1;
    bVar1 = false;
    if ((-1 < nr_local) && (bVar1 = false, '/' < *s_local)) {
      bVar1 = *s_local < ':';
    }
    if (!bVar1) break;
    result = result * 10 + *s_local + -0x30;
    s_local = s_local + 1;
  }
  *d = result;
  return s_local;
}