void _itoa_dec(uint val,char *buf)

{
  uint i;
  char *buf_local;
  uint val_local;
  
  val_local = val;
  for (i = 0; i < 10; i = i + 1) {
    if ((val_local == 0) && (i != 0)) {
      buf[9 - i] = ' ';
    }
    else {
      buf[9 - i] = "0123456789"[(ulong)val_local % 10];
    }
    val_local = val_local / 10;
  }
  return;
}