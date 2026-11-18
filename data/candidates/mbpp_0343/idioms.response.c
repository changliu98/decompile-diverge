void func0(char *str, int *letters, int *digits)
{
  int l = 0;
  int d = 0;
  while (*str) {
    if (((*__ctype_b_loc ())[(int) (((unsigned char) *str))] & (unsigned short) _ISdigit))
      d++;
    else if (((*__ctype_b_loc ())[(int) (((unsigned char) *str))] & (unsigned short) _ISalpha))
      l++;
    str++;
  }
  *letters = l;
  *digits = d;
}