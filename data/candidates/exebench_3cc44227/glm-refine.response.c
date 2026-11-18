const char *__cdecl js_itoa(char *out, unsigned int a)
{
  char buf[32];
  int i = 0;
  char *s = out;

  // Convert integer to string in reverse order
  if (a == 0) {
    buf[i++] = '0';
  } else {
    while (a) {
      buf[i++] = a % 10 + '0';
      a /= 10;
    }
  }

  // Reverse the string and write to the output buffer
  while (i) {
    *s++ = buf[--i];
  }

  *s = '\0';
  return out;
}