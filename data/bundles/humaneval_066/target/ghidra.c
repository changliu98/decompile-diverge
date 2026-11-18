int func0(char *s)

{
  int i;
  int sum;
  char *s_local;
  
  sum = 0;
  for (i = 0; s[i] != '\0'; i = i + 1) {
    if (('@' < s[i]) && (s[i] < '[')) {
      sum = s[i] + sum;
    }
  }
  return sum;
}