char *func0(char **strings, int count)
{
  char *longest = "";
  int longest_length = 0;
  int i;
  int current_length;
  for (i = 0; i < count; i++) {
    current_length = strlen(strings[i]);
    if (current_length > longest_length) {
      longest = strings[i];
      longest_length = current_length;
    }
  }
  return longest;
}