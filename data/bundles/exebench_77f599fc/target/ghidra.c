void uppercaser(char *string)

{
  int i;
  char *string_local;
  
  for (i = 0; string[i] != '\0'; i = i + 1) {
    if (('`' < string[i]) && (string[i] < '{')) {
      string[i] = string[i] + -0x20;
    }
  }
  return;
}