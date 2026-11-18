char **__cdecl func0(const char *text)
{
  size_t len = strlen(text);

  // Upper bound on token count: at most len/2 tokens (each needs >=1 char + separator),
  // plus 1 slot for the NULL terminator.
  char **result = (char **)malloc(8 * ((len >> 1) + 1));
  int count = 0;

  // strtok mutates its input, so work on a duplicate.
  char *copy = strdup(text);
  char *token;

  for (token = strtok(copy, " "); token; token = strtok(NULL, " "))
  {
    // Strip trailing punctuation: '.' ',' '!' '?' ';' ':'
    // Note: the first character is never stripped (loop stops when end == token).
    char *end = token + strlen(token) - 1;
    while (end > token)
    {
      char c = *end;
      if (c != '.' && c != ',' && c != '!' && c != '?' && c != ';' && c != ':')
        break;
      *end = '\0';
      --end;
    }

    // Keep only tokens with length >= 4.
    if (strlen(token) >= 4)
      result[count++] = strdup(token);
  }

  result[count] = NULL;
  free(copy);
  return result;
}