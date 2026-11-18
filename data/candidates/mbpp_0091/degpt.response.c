_Bool func0(char **str1,char *sub_str,int size)

{
  char *pcVar1;
  int i;
  int size_local;
  char *sub_str_local;
  char **str1_local;
  
  i = 0;
  while( true ) {
    if (size <= i) {
      return false;
    }
    pcVar1 = strstr(str1[i],sub_str);
    if (pcVar1 != (char *)0x0) break;
    i = i + 1;
  }
  return true;
}