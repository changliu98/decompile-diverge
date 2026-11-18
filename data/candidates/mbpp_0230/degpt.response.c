char * func0(char *str1,char *char_replacement)

{
  int i;
  int j;
  char *char_replacement_local;
  char *str1_local;
  
  j = 0;
  for (i = 0; str1[i] != '\0'; i = i + 1) {
    if (str1[i] == ' ') {
      func0::str2[j] = *char_replacement;
    }
    else {
      func0::str2[j] = str1[i];
    }
    j = j + 1;
  }
  func0::str2[j] = '\0';
  return func0::str2;
}