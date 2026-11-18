int func0(int num)

{
  bool bVar1;
  size_t sVar2;
  int j;
  int isPalindrome;
  int len;
  char numstr [20];
  int i;
  int num_local;
  
  do {
    i = num + 1;
    if (0x7ffffffe < i) {
      return -1;
    }
    sprintf(numstr,"%d",(ulong)(uint)i);
    sVar2 = strlen(numstr);
    bVar1 = true;
    for (j = 0; j < (int)sVar2 / 2; j = j + 1) {
      if (numstr[j] != numstr[((int)sVar2 + -1) - j]) {
        bVar1 = false;
        break;
      }
    }
    num = i;
    if (bVar1) {
      return i;
    }
  } while( true );
}