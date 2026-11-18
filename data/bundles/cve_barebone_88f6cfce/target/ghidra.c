void append_command(char_u *cmd)

{
  char_u *pcVar1;
  size_t sVar2;
  int iVar3;
  char_u *d;
  char_u *s;
  char_u *cmd_local;
  
  s = cmd;
  cmd_local = cmd;
  strcat((char *)IObuff,": ");
  pcVar1 = IObuff;
  sVar2 = strlen((char *)IObuff);
  d = pcVar1 + sVar2;
  do {
    while( true ) {
      if (*s == '\0' || 0x3f9 < (long)d - (long)IObuff) {
        *d = '\0';
        return;
      }
      if (enc_utf8 == 0) break;
      if ((*s == 0xc2) && (s[1] == 0xa0)) goto LAB_00101a34;
LAB_00101a7e:
      if (has_mbyte == 0) {
        *d = *s;
        d = d + 1;
        s = s + 1;
      }
      else {
        mb_copy_char(&s,&d);
      }
    }
    if (*s != 0xa0) goto LAB_00101a7e;
LAB_00101a34:
    iVar3 = 1;
    if (enc_utf8 != 0) {
      iVar3 = 2;
    }
    s = s + iVar3;
    strcpy((char *)d,"<a0>");
    d = d + 4;
  } while( true );
}