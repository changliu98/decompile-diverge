char * func0(char *text)

{
  size_t sVar1;
  char *result;
  uchar byte;
  uint j;
  uint i;
  uint crc;
  char *text_local;
  char *local_10;
  
  sVar1 = strlen(text);
  if (sVar1 == 0) {
    local_10 = strdup("None");
  }
  else {
    crc = 0xffffffff;
    for (i = 0; text[i] != '\0'; i = i + 1) {
      crc = crc ^ (byte)text[i];
      for (j = 0; j < 8; j = j + 1) {
        if ((crc & 1) == 0) {
          crc = crc >> 1;
        }
        else {
          crc = crc >> 1 ^ 0xedb88320;
        }
      }
    }
    local_10 = malloc(9);
    if (local_10 != (char *)0x0) {
      sprintf(local_10,"%08X",(ulong)(crc ^ 0xffffffff));
    }
  }
  return local_10;
}