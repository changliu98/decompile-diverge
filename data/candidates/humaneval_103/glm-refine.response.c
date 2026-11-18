char *__cdecl func0(int n, int m)
{
  char *buffer;
  int index;
  int num;

  // If n is greater than m, return a static empty string
  if (n > m)
    return "";

  // Calculate the midpoint
  num = (n + m) / 2;

  // Allocate a 33-byte buffer (32 characters + null terminator)
  buffer = (char *)malloc(33);
  *buffer = 0;
  buffer[32] = 0;

  // Start at the end of the buffer and write binary digits backwards
  index = 31;
  do
  {
    // '0' is 48 in ASCII. (num % 2) gives 0 or 1.
    buffer[index] = (num % 2) + '0';
    index--;
    num /= 2;
  }
  while (num > 0);

  // Return the pointer to the start of the generated binary string
  return &buffer[index + 1];
}