char * func0(char *test_str,int K)

{
  size_t sVar1;
  char *__s;
  size_t len;
  char *token;
  char *res;
  char temp_copy [1000];
  int K_local;
  char *test_str_local;
  
  strncpy(temp_copy,test_str,1000);
  temp_copy[999] = '\0';
  sVar1 = strlen(test_str);
  __s = malloc(sVar1 + 1);
  if (__s == (char *)0x0) {
    perror("malloc failed");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  *__s = '\0';
  token = strtok(temp_copy," ");
  while (token != (char *)0x0) {
    sVar1 = strlen(token);
    if ((int)sVar1 != K) {
      strcat(__s,token);
      strcat(__s," ");
    }
    token = strtok((char *)0x0," ");
  }
  sVar1 = strlen(__s);
  if ((sVar1 != 0) && (__s[sVar1 - 1] == ' ')) {
    __s[sVar1 - 1] = '\0';
  }
  return __s;
}