int parse_uuid(char *str,int *uuid)

{
  char cVar1;
  char *pcVar2;
  int n;
  char c;
  int i;
  int hit;
  int *uuid_local;
  char *str_local;
  
  hit = 0;
  for (i = 0; str_local = str, i < 4; i = i + 1) {
    uuid[i] = 0;
  }
  do {
    while( true ) {
      cVar1 = *str_local;
      if (cVar1 == '\0') {
        if (hit == 0x20) {
          return 1;
        }
        return 0;
      }
      if ((cVar1 < '0') || ('9' < cVar1)) break;
      n = cVar1 + -0x30;
LAB_0010130c:
      if (hit < 0x20) {
        uuid[hit / 8] = uuid[hit / 8] << 4;
        uuid[hit / 8] = n + uuid[hit / 8];
      }
      hit = hit + 1;
      str_local = str_local + 1;
    }
    if (('`' < cVar1) && (cVar1 < 'g')) {
      n = cVar1 + -0x57;
      goto LAB_0010130c;
    }
    if (('@' < cVar1) && (cVar1 < 'G')) {
      n = cVar1 + -0x37;
      goto LAB_0010130c;
    }
    pcVar2 = strchr(":. -",(int)cVar1);
    str_local = str_local + 1;
    if (pcVar2 == (char *)0x0) {
      return 0;
    }
  } while( true );
}