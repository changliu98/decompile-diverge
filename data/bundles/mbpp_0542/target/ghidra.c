char * func0(char *text)

{
  int i;
  char *text_local;
  
  strcpy(func0::result,text);
  for (i = 0; func0::result[i] != '\0'; i = i + 1) {
    if (((func0::result[i] == ' ') || (func0::result[i] == ',')) || (func0::result[i] == '.')) {
      func0::result[i] = ':';
    }
  }
  return func0::result;
}