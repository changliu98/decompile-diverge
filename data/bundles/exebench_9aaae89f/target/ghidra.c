void pick(int *np,int *nr)

{
  int *nr_local;
  int *np_local;
  
  *nr = *nr + 1;
  if (0x2ff < *nr) {
    *np = *np + 1;
    *nr = 0;
  }
  if (0xb3 < *np) {
    *np = 0;
  }
  return;
}