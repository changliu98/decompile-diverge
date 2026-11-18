void wdc_UtilsDeleteCharFromString(char *buffer,int buffSize,char charToRemove)

{
  bool bVar1;
  int count;
  int i;
  char charToRemove_local;
  int buffSize_local;
  char *buffer_local;
  
  count = 0;
  if ((buffer != (char *)0x0) && (buffSize != 0)) {
    i = 0;
    while( true ) {
      bVar1 = false;
      if (i < buffSize) {
        bVar1 = buffer[i] != '\0';
      }
      if (!bVar1) break;
      if (buffer[i] != charToRemove) {
        buffer[count] = buffer[i];
        count = count + 1;
      }
      i = i + 1;
    }
    buffer[count] = '\0';
  }
  return;
}