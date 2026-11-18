char *__cdecl func0(int n)
{
  char *ptr;
  char *out;
  int i;
  int len;

  // Calculate the total length required for the string.
  // Start with 2 for the "0" character and the null terminator.
  len = 2;
  for (i = 1; i <= n; ++i)
    len += snprintf(NULL, 0, " %d", i);

  // Allocate memory for the resulting string
  out = (char *)malloc(len);
  if (!out)
    return NULL;

  // Write the initial "0" and set ptr to the end of the current string
  ptr = out + sprintf(out, "0");

  // Append the rest of the numbers to the string
  for (i = 1; i <= n; ++i)
    ptr += sprintf(ptr, " %d", i);

  return out;
}