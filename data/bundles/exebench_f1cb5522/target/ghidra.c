void argorder(int ix1,int ix2,int *ox1,int *ox2)

{
  int tmp;
  int *ox2_local;
  int *ox1_local;
  int ix2_local;
  int ix1_local;
  
  ix2_local = ix2;
  ix1_local = ix1;
  if (ix2 < ix1) {
    ix2_local = ix1;
    ix1_local = ix2;
  }
  *ox1 = ix1_local;
  *ox2 = ix2_local;
  return;
}