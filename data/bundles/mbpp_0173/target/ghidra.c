char * func0(char *text)

{
  long lVar1;
  char *__src;
  char *__dest;
  size_t sVar2;
  ushort **ppuVar3;
  undefined8 uStack_40;
  char acStack_38 [8];
  char *local_30;
  unsigned_long __vla_expr0;
  char *local_20;
  int j;
  int i;
  char *text_local;
  
                    /* Unresolved local var: char[266] temp@[???] */
  i = 0;
  j = 0;
  uStack_40 = 0x101213;
  text_local = text;
  sVar2 = strlen(text);
  __vla_expr0 = sVar2 + 1;
  lVar1 = -(sVar2 + 0x10 & 0xfffffffffffffff0);
  local_30 = acStack_38 + lVar1;
  local_20 = acStack_38;
  for (; __dest = text_local, __src = local_30, text_local[i] != '\0'; i = i + 1) {
    *(undefined8 *)((long)&uStack_40 + lVar1) = 0x101254;
    ppuVar3 = __ctype_b_loc();
    if (((*ppuVar3)[(int)text_local[i]] & 8) != 0) {
      local_30[j] = text_local[i];
      j = j + 1;
    }
  }
  local_30[j] = '\0';
  *(undefined8 *)((long)&uStack_40 + lVar1) = 0x1012b9;
  strcpy(__dest,__src);
  return text_local;
}