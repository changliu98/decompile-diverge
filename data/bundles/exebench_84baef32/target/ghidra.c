void _itoa_hex(uint val,char *buf)

{
  uint i;
  char *buf_local;
  uint val_local;
  
  val_local = val;
  for (i = 0; i < 8; i = i + 1) {
    buf[7 - i] = "0123456789ABCD"[val_local & 0xf];
    val_local = val_local >> 4;
  }
  return;
}