void __cdecl check_int(int *x, int *y, char *ret)
{
  // Default value is 'f' (ASCII 102)
  char result = 'f';

  // Check if the distance between the two pointers is exactly 4 bytes
  // (which is the size of one 'int' on most 32/64-bit systems)
  if ((char *)y - (char *)x == 4)
    result = 't'; // ASCII 116

  *ret = result;
}