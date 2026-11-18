int func0(char *str1)

{
  int total;
  char *str1_local;
  
  total = 0;
  for (str1_local = str1; *str1_local != '\0'; str1_local = str1_local + 1) {
    total = total + 1;
  }
  return total;
}