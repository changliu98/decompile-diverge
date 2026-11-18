char *is_valid(char *name)
{
  int i; int len;
  int num_digit = 0;
  int num_dot = 0;
  char first;
  char *last;
  len = strlen(name);
  if (len < 5)
    return "No";
  first = name[0];
  if (first < 'A' || (first > 'Z' && first < 'a') || first > 'z')
    return "No";
  last = name + len - 4;
  if (strcmp(last, ".txt") != 0 && strcmp(last, ".exe") != 0 &&
      strcmp(last, ".dll") != 0)
    return "No";
  for (i = 0; i < len; i++)
  {
    if (name[i] >= '0' && name[i] <= '9')
      num_digit++;
    if (name[i] == '.')
      num_dot++;
  }
  if (num_digit > 3 || num_dot != 1)
    return "No";
  return "Yes";
}