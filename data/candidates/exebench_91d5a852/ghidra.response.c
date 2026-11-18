void to_bytes(int val,char *bytes)

{
  char *bytes_local;
  int val_local;
  
  *bytes = (char)val;
  bytes[1] = (char)((uint)val >> 8);
  bytes[2] = (char)((uint)val >> 0x10);
  bytes[3] = (char)((uint)val >> 0x18);
  return;
}