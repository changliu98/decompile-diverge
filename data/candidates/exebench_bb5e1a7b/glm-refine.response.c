char *__cdecl ReadNumber(char *s, double *num)
{
  int int_part = 0;
  int frac_part = 0;
  double sign = 1.0;
  double scale = 1.0;

  // Parse sign
  while (*s == '+' || *s == '-')
  {
    if (*s == '-')
      *(unsigned long long *)&sign ^= 0x8000000000000000ULL; // Toggle sign bit
    s++;
  }

  // Parse integer part
  while (*s >= '0' && *s <= '9')
  {
    int_part = *s + 10 * int_part - '0';
    s++;
  }

  // Parse fractional part
  if (*s != '\0')
  {
    if (*s == '.')
    {
      s++;
      while (*s >= '0' && *s <= '9')
      {
        frac_part = *s + 10 * frac_part - '0';
        scale *= 10.0;
        s++;
      }
    }
    *num = sign * ((double)int_part + (double)frac_part / scale);
  }
  else
  {
    *num = (double)int_part * sign;
  }

  return s;
}