char *isBalanced(char *s1, char *s2) {
  int count = 0;
  int len1 = strlen(s1);
  int len2 = strlen(s2);
  int flag = 1;
  int i;
  for (i = 0; i < len1; i++) {
    if (s1[i] == '(') count++;
    if (s1[i] == ')') count--;
    if (count < 0) flag = 0;
  }
  for (i = 0; i < len2; i++) {
    if (s2[i] == '(') count++;
    if (s2[i] == ')') count--;
    if (count < 0) flag = 0;
  }
  if (count == 0 && flag) return "YES";
  count = 0;
  flag = 1;
  for (i = 0; i < len2; i++) {
    if (s2[i] == '(') count++;
    if (s2[i] == ')') count--;
    if (count < 0) flag = 0;
  }
  for (i = 0; i < len1; i++) {
    if (s1[i] == '(') count++;
    if (s1[i] == ')') count--;
    if (count < 0) flag = 0;
  }
  if (count == 0 && flag) return "YES";
  return "NO";
}