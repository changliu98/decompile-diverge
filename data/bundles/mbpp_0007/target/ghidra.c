char ** func0(char *text)

{
  size_t sVar1;
  char **ppcVar2;
  char *__s;
  char *pcVar3;
  bool bVar4;
  char *end;
  char *token;
  char *copy;
  int count;
  char **result;
  char *text_local;
  
  sVar1 = strlen(text);
  ppcVar2 = malloc(((sVar1 >> 1) + 1) * 8);
  count = 0;
  __s = strdup(text);
  token = strtok(__s," ");
  while (token != (char *)0x0) {
    sVar1 = strlen(token);
    end = token + sVar1;
    while( true ) {
      end = end + -1;
      bVar4 = false;
      if ((((token < end) && (bVar4 = true, *end != '.')) && (bVar4 = true, *end != ',')) &&
         (((bVar4 = true, *end != '!' && (bVar4 = true, *end != '?')) && (bVar4 = true, *end != ';')
          ))) {
        bVar4 = *end == ':';
      }
      if (!bVar4) break;
      *end = '\0';
    }
    sVar1 = strlen(token);
    if (3 < sVar1) {
      pcVar3 = strdup(token);
      ppcVar2[count] = pcVar3;
      count = count + 1;
    }
    token = strtok((char *)0x0," ");
  }
  ppcVar2[count] = (char *)0x0;
  free(__s);
  return ppcVar2;
}