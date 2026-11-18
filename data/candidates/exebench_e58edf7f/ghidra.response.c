void toUpperCase(char *str)

{
  char smallCase;
  int index;
  char *str_local;
  
  for (index = 0; str[index] != '\0'; index = index + 1) {
    for (smallCase = 'a'; smallCase < '{'; smallCase = smallCase + '\x01') {
      if (str[index] == smallCase) {
        str[index] = str[index] + -0x20;
      }
    }
  }
  return;
}