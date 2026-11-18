char *__cdecl func0(int a, int b, int c, int d)
{
  int total = 0;
  int index = 0;
  int i;
  char *result;

  // Calculate the total required allocation size, ignoring negative lengths
  if (a > 0) total += a;
  if (b > 0) total += b;
  if (c > 0) total += c;
  if (d > 0) total += d;

  // Allocate memory for the string plus a null terminator
  result = (char *)malloc(total + 1);
  if (!result)
  {
    perror("Failed to allocate memory");
    exit(1);
  }

  // Fill the allocated buffer with specific characters based on the counts
  for (i = 0; i < a; ++i)
    result[index++] = 'p'; // ASCII 112

  for (i = 0; i < b; ++i)
    result[index++] = 'q'; // ASCII 113

  for (i = 0; i < c; ++i)
    result[index++] = 'r'; // ASCII 114

  for (i = 0; i < d; ++i)
    result[index++] = 's'; // ASCII 115

  // Null-terminate the string
  result[index] = '\0';

  return result;
}