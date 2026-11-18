char* isAccepted(char* s) {
  char* str = s;
  char vowels[] = "AEIOUaeiou";
  int flag[10];
  int count = 0;
  int i, j;
  memset(flag, 0, sizeof(flag));
  for (i = 0; str[i] != '\0'; i++) {
    for (j = 0; j < 10; j++) {
      if (str[i] == vowels[j] && flag[j] == 0) {
        flag[j] = 1;
        count++;
        break;
      }
    }
  }
  if (count >= 5)
    return "accepted";
  else
    return "not accepted";
}