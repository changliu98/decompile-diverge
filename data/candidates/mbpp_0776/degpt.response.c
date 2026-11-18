int func0(char *test_str)

{
  int iVar1;
  size_t sVar2;
  char *pcVar3;
  int idx;
  int len;
  char *vow_list;
  int res;
  char *test_str_local;
  
  res = 0;
  sVar2 = strlen(test_str);
  iVar1 = (int)sVar2;
  idx = 1;
  do {
    if (iVar1 + -1 <= idx) {
      pcVar3 = strchr("aeiou",(int)*test_str);
      if (pcVar3 == (char *)0x0) {
        pcVar3 = strchr("aeiou",(int)test_str[1]);
        if (pcVar3 != (char *)0x0) {
          res = res + 1;
        }
      }
      pcVar3 = strchr("aeiou",(int)test_str[iVar1 + -1]);
      if (pcVar3 == (char *)0x0) {
        pcVar3 = strchr("aeiou",(int)test_str[iVar1 + -2]);
        if (pcVar3 != (char *)0x0) {
          res = res + 1;
        }
      }
      return res;
    }
    pcVar3 = strchr("aeiou",(int)test_str[idx]);
    if (pcVar3 == (char *)0x0) {
      pcVar3 = strchr("aeiou",(int)test_str[idx + -1]);
      if (pcVar3 == (char *)0x0) {
        pcVar3 = strchr("aeiou",(int)test_str[idx + 1]);
        if (pcVar3 == (char *)0x0) goto LAB_00101292;
      }
      res = res + 1;
    }
LAB_00101292:
    idx = idx + 1;
  } while( true );
}