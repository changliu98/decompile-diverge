void func0(char *str, char *out)
{
  int i;
  int length = strlen(str);
  for (i = 0; i < length; i++) {
    char c = str[i];
    if (c >= 'a' && c <= 'z') {
      c -= 'a';
      c += 'A';
    } else if (c >= 'A' && c <= 'Z') {
      c -= 'A';
      c += 'a';
    }
    out[i] = c;
  }
  out[length] = '\0';
}