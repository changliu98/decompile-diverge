char *func0(char *str) {
  int i, len, flag1, flag2, flag3;
  flag1 = flag2 = flag3 = 0;
  len = strlen(str);
  for (i = 0; i < len; i++) {
    if (isupper(str[i])) flag1 = 1;
    if (islower(str[i])) flag2 = 1;
    if (isdigit(str[i])) flag3 = 1;
  }
  static char result[100];
  result[0] = '\0';
  if (!flag1) strcat(result, "String must have 1 upper case character,");
  if (!flag2) strcat(result, "String must have 1 lower case character,");
  if (!flag3) strcat(result, "String must have 1 number,");
  if (len < 8) strcat(result, "String length should be atleast 8,");
  if (flag1 && flag2 && flag3 && len >= 8)
    strcpy(result, "Valid string.");
  else {
    int l = strlen(result) - 1;
    if (result[l] == ',') result[l] = '\0';
  }
  return result;
}