
void uppercaser(char *string) {
  int i = 0;
  while (string[i] != '\0') {
    if (string[i] >= 97 && string[i] <= 122)


      string[i] -= 32;

    ++i;
  }
}
