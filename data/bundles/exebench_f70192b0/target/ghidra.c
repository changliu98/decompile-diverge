int i_to_str(int val,char *str)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char ch;
  int digit;
  int ni;
  char *begin;
  char *s;
  int i;
  int len;
  char *str_local;
  int val_local;
  
  str_local = str;
  val_local = val;
  if (val < 0) {
    str_local = str + 1;
    *str = '-';
    val_local = -val;
  }
  s = str_local;
  do {
    iVar2 = val_local / 10;
    pcVar3 = s + 1;
    *s = (char)(val_local % 10) + '0';
    s = pcVar3;
    val_local = iVar2;
  } while (iVar2 != 0);
  *pcVar3 = '\0';
  iVar2 = (int)pcVar3 - (int)str_local;
  for (i = 0; i < iVar2 / 2; i = i + 1) {
    cVar1 = str_local[i];
    str_local[i] = str_local[(iVar2 + -1) - i];
    str_local[(iVar2 + -1) - i] = cVar1;
  }
  return (int)pcVar3 - (int)str;
}