char * func0(char *word,char *result)

{
  size_t sVar1;
  int i;
  int length;
  char *result_local;
  char *word_local;
  
  sVar1 = strlen(word);
  for (i = 0; i < (int)sVar1; i = i + 1) {
    result[i] = word[i];
  }
  result[(int)sVar1] = '\0';
  return result;
}