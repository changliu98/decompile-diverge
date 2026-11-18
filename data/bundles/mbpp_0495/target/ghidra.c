char * func0(char *str1)

{
  int j;
  int i;
  char *str1_local;
  
  j = 0;
  for (i = 0; str1[i] != '\0'; i = i + 1) {
    if ((str1[i] < 'a') || ('z' < str1[i])) {
      func0::result[j] = str1[i];
      j = j + 1;
    }
  }
  func0::result[j] = '\0';
  return func0::result;
}