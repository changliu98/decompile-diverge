int func0(char *str1)

{
  int count;
  char *str1_local;
  
  count = 0;
  for (str1_local = str1; *str1_local != '\0'; str1_local = str1_local + 1) {
    count = count + 1;
  }
  return count;
}