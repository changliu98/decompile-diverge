const char *__cdecl func0(const char *a, const char *b)
{
  char *end = NULL;
  char *a_copy = strdup(a);
  char *b_copy = strdup(b);
  
  // Replace commas with periods for standard decimal parsing
  for (char *p = a_copy; *p; ++p)
  {
    if (*p == ',')
      *p = '.';
  }
  
  for (char *p = b_copy; *p; ++p)
  {
    if (*p == ',')
      *p = '.';
  }

  // Parse numbers and check for conversion errors
  double val_a = strtod(a_copy, &end);
  if (*end != '\0')
  {
    free(a_copy);
    free(b_copy);
    return "Invalid input";
  }

  double val_b = strtod(b_copy, &end);
  if (*end != '\0')
  {
    free(a_copy);
    free(b_copy);
    return "Invalid input";
  }

  free(a_copy);
  free(b_copy);

  // Compare values and return the appropriate result
  if (val_a == val_b)
  {
    return "None";
  }
  else if (val_a < val_b)
  {
    return b;
  }
  else
  {
    return a;
  }
}