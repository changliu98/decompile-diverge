int func0(int num)

{
  char cVar1;
  int iVar2;
  size_t sVar3;
  int i;
  char temp;
  int len;
  int x;
  char rev_str [12];
  char num_str [12];
  int num_local;
  
  do {
    x = num + -1;
    if (x < 1) {
      return 0;
    }
    sprintf(num_str,"%d",(ulong)(uint)x);
    strcpy(rev_str,num_str);
    sVar3 = strlen(rev_str);
    iVar2 = (int)sVar3;
    for (i = 0; i < iVar2 / 2; i = i + 1) {
      cVar1 = rev_str[i];
      rev_str[i] = rev_str[(iVar2 + -1) - i];
      rev_str[(iVar2 + -1) - i] = cVar1;
    }
    iVar2 = strcmp(num_str,rev_str);
    num = x;
  } while (iVar2 != 0);
  return x;
}