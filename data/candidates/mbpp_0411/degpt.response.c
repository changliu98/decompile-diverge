char * func0(char *word,char *result)

{
  bool bVar1;
  int iVar2;
  int i;
  int capitalize;
  int index;
  char *result_local;
  char *word_local;
  
  index = 0;
  bVar1 = true;
  for (i = 0; word[i] != '\0'; i = i + 1) {
    if (word[i] == '_') {
      bVar1 = true;
    }
    else {
      if (bVar1) {
        iVar2 = toupper((int)word[i]);
        result[index] = (char)iVar2;
        bVar1 = false;
      }
      else {
        result[index] = word[i];
      }
      index = index + 1;
    }
  }
  result[index] = '\0';
  return result;
}