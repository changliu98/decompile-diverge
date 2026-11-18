int val_seg(int val)

{
  int r;
  int val_local;
  
  r = 0;
  val_local = val >> 7;
  if ((val_local & 0xf0U) != 0) {
    val_local = val >> 0xb;
    r = 4;
  }
  if ((val_local & 0xcU) != 0) {
    val_local = val_local >> 2;
    r = r + 2;
  }
  if ((val_local & 2U) != 0) {
    r = r + 1;
  }
  return r;
}