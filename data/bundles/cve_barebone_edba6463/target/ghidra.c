void process_COM(uchar *Data,int length)

{
  byte bVar1;
  int a;
  int nch;
  char Comment [16001];
  int ch;
  int length_local;
  uchar *Data_local;
  
  nch = 0;
  length_local = length;
  if (16000 < length) {
    length_local = 16000;
  }
  for (a = 2; a < length_local; a = a + 1) {
    bVar1 = Data[a];
    if ((bVar1 != 0xd) || (Data[a + 1] != '\n')) {
      if ((bVar1 < 0x20) && ((bVar1 != 10 && (bVar1 != 9)))) {
        Comment[nch] = '?';
      }
      else {
        Comment[nch] = bVar1;
      }
      nch = nch + 1;
    }
  }
  Comment[nch] = '\0';
  if (ShowTags != 0) {
    printf("COM marker comment: %s\n",Comment);
  }
  strcpy(ImageInfo.Comments,Comment);
  return;
}