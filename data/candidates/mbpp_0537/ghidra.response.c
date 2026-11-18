char * func0(char *str1)

{
  int iVar1;
  int i;
  char *word;
  int word_count;
  char *words [100];
  char *str1_local;
  
  word_count = 0;
  word = strtok(str1," ");
  do {
    if (word == (char *)0x0) {
      return "None";
    }
    for (i = 0; i < word_count; i = i + 1) {
      iVar1 = strcmp(words[i],word);
      if (iVar1 == 0) {
        return word;
      }
    }
    words[word_count] = word;
    word = strtok((char *)0x0," ");
    word_count = word_count + 1;
  } while( true );
}