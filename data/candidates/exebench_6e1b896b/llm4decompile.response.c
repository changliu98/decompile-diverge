void break_at(char *str, char c)
{
  char *ptr = strchr(str, c);
  if (ptr) {
    *ptr = '\0';
  }
}