int count_vowels(char *str, char *vowels)
{
  int count = 0;
  char *p;
  while (*str != '\0') {
    for (p = vowels; *p != '\0'; p++) {
      if (*str == *p) {
        count++;
        break;
      }
    }
    str++;
  }
  return count;
}