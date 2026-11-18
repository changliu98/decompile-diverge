char *get_min(char *a, char *b)
{
  char *end;
  char *a_mod = strdup(a);
  char *b_mod = strdup(b);
  int i = 0;
  for (i = 0; a_mod[i] != '\0'; i++)
  {
    if (a_mod[i] == ',')
    {
      a_mod[i] = '.';
    }
  }
  int i2 = 0;
  for (i2 = 0; b_mod[i2] != '\0'; i2++)
  {
    if (b_mod[i2] == ',')
    {
      b_mod[i2] = '.';
    }
  }
  double a_double = strtod(a_mod, &end);
  if (*end != '\0')
  {
    free(a_mod);
    free(b_mod);
    return "Invalid input";
  }
  double b_double = strtod(b_mod, &end);
  if (*end != '\0')
  {
    free(a_mod);
    free(b_mod);
    return "Invalid input";
  }
  free(a_mod);
  free(b_mod);
  if (a_double == b_double)
  {
    return "None";
  }
  if (a_double > b_double)
  {
    return b;
  }
  if (a_double < b_double)
  {
    return a;
  }
}