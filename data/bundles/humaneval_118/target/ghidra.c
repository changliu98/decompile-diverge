char * func0(char *word)

{
  size_t sVar1;
  char *pcVar2;
  int i;
  size_t len;
  char *vowels;
  char *word_local;
  
  sVar1 = strlen(word);
  i = (int)sVar1 + -2;
  while( true ) {
    if (i < 1) {
      func0::out[0] = '\0';
      return func0::out;
    }
    pcVar2 = strchr("AEIOUaeiou",(int)word[i]);
    if (((pcVar2 != (char *)0x0) &&
        (pcVar2 = strchr("AEIOUaeiou",(int)word[i + 1]), pcVar2 == (char *)0x0)) &&
       (pcVar2 = strchr("AEIOUaeiou",(int)word[i + -1]), pcVar2 == (char *)0x0)) break;
    i = i + -1;
  }
  func0::out[0] = word[i];
  return func0::out;
}