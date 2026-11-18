char *func0(char *str1){
  int i = 0;
  int j = 1;
  int k = 0;
  for (i = j; i <= strlen(str1); i++){
    if (i % 2 == 0){
      str2[k++] = str1[i - 1];
    }
  }
  str2[k] = '\0';
  return str2;
}