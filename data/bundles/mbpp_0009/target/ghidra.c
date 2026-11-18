int func0(char *str)

{
  long lVar1;
  bool bVar2;
  char *pcVar3;
  char *__src;
  size_t sVar4;
  undefined8 uStack_50;
  char *local_48;
  int j;
  int equal;
  int i;
  unsigned_long __vla_expr0;
  undefined1 *local_28;
  int n;
  char *str_local;
  
                    /* Unresolved local var: char[196] tmp@[???] */
  uStack_50 = 0x101205;
  str_local = str;
  sVar4 = strlen(str);
  pcVar3 = str_local;
  n = (int)sVar4;
  __vla_expr0 = (unsigned_long)(n * 2 + 1);
  lVar1 = -(__vla_expr0 + 0xf & 0xfffffffffffffff0);
  local_48 = (char *)((long)&local_48 + lVar1);
  local_28 = (undefined1 *)&local_48;
  *(undefined8 *)((long)&uStack_50 + lVar1) = 0x10123d;
  strcpy((char *)((long)&local_48 + lVar1),pcVar3);
  __src = str_local;
  pcVar3 = local_48;
  *(undefined8 *)((long)&uStack_50 + lVar1) = 0x10124a;
  strcat(pcVar3,__src);
  i = 1;
  do {
    if (n < i) {
      return n;
    }
    bVar2 = true;
    for (j = 0; j < n; j = j + 1) {
      if (str_local[j] != local_48[i + j]) {
        bVar2 = false;
        break;
      }
    }
    if (bVar2) {
      return i;
    }
    i = i + 1;
  } while( true );
}