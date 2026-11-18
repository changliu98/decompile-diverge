void Swap8Bytes(char *bytes)

{
  char cVar1;
  char t;
  char *bytes_local;
  
  cVar1 = *bytes;
  *bytes = bytes[7];
  bytes[7] = cVar1;
  cVar1 = bytes[1];
  bytes[1] = bytes[6];
  bytes[6] = cVar1;
  cVar1 = bytes[2];
  bytes[2] = bytes[5];
  bytes[5] = cVar1;
  cVar1 = bytes[3];
  bytes[3] = bytes[4];
  bytes[4] = cVar1;
  return;
}