void removeCharactersInPlace(char *string, char *characters) {
  char *read = string;
  char *write = string;
  while (*read) {
    char found = 0;
    char *c = characters;
    do {
      found = *read == *c;
      c++;
    } while (!found && *c);
    if (!found) {
      *write = *read;
      write++;
    }
    read++;
  }
  *write = 0;
}