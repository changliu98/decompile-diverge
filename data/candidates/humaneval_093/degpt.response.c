void func0(char *message,char *out)

{
  int iVar1;
  ushort **ppuVar2;
  char w;
  int j;
  int i;
  char *vowels;
  char *out_local;
  char *message_local;
  
  i = 0;
  do {
    if (message[i] == '\0') {
      out[i] = '\0';
      return;
    }
    w = message[i];
    ppuVar2 = __ctype_b_loc();
    if (((*ppuVar2)[(int)w] & 0x200) == 0) {
      ppuVar2 = __ctype_b_loc();
      if (((*ppuVar2)[(int)w] & 0x100) != 0) {
        iVar1 = tolower((int)w);
        w = (char)iVar1;
      }
    }
    else {
      iVar1 = toupper((int)w);
      w = (char)iVar1;
    }
    for (j = 0; "aeiouAEIOU"[j] != '\0'; j = j + 1) {
      if (w == "aeiouAEIOU"[j]) {
        if (j < 10) {
          w = w + '\x02';
        }
        break;
      }
    }
    out[i] = w;
    i = i + 1;
  } while( true );
}