void decrypt(char *string,int shift)

{
  int i;
  int shift_local;
  char *string_local;
  
  for (i = 0; string[i] != '\0'; i = i + 1) {
    if (string[i] == '-') {
      string[i] = ' ';
    }
    else {
      string[i] = (char)((string[i] + -0x61 + shift % 0x1a) % 0x1a) + 'a';
    }
  }
  return;
}