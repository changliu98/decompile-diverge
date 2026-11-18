void func0(char *s,char *c,char *result,char *palindrome)

{
  bool bVar1;
  size_t sVar2;
  char *__s;
  char *__src;
  int i_1;
  _Bool is_palindrome;
  int n_len;
  _Bool found;
  char *temp;
  int i;
  int ni;
  char *n;
  int len;
  char *palindrome_local;
  char *result_local;
  char *c_local;
  char *s_local;
  
  sVar2 = strlen(s);
  __s = malloc((long)((int)sVar2 + 1));
  ni = 0;
  for (i = 0; s[i] != '\0'; i = i + 1) {
    bVar1 = false;
    for (temp = c; *temp != '\0'; temp = temp + 1) {
      if (s[i] == *temp) {
        bVar1 = true;
        break;
      }
    }
    if (!bVar1) {
      __s[ni] = s[i];
      ni = ni + 1;
    }
  }
  __s[ni] = '\0';
  sVar2 = strlen(__s);
  bVar1 = true;
  i_1 = 0;
  do {
    if ((int)sVar2 / 2 <= i_1) {
LAB_00101360:
      strcpy(result,__s);
      __src = "False";
      if (bVar1) {
        __src = "True";
      }
      strcpy(palindrome,__src);
      free(__s);
      return;
    }
    if (__s[i_1] != __s[((int)sVar2 + -1) - i_1]) {
      bVar1 = false;
      goto LAB_00101360;
    }
    i_1 = i_1 + 1;
  } while( true );
}