void itoa(char *str, int base, long val)
{
  char *s = str;
  char *start = str;
  char *end;
  char *end2;
  char tmp;
  int remainder;
  unsigned long uval = (unsigned long)val;
  int div = 10;
  if (base == 100 && val < 0) {
    *start++ = '-';
    s = start;
    uval = (unsigned long)-val;
  }
  else if (base == 120) {
    div = 16;
  }
  do {
    remainder = uval % div;
    *start++ = (remainder < 10 ? '0' : 'a' - 10) + remainder;
  } while (uval /= div);
  *start = '\0';
  end = s;
  end2 = start - 1;
  while (end < end2) {
    tmp = *end;
    *end = *end2;
    *end2 = tmp;
    end++;
    end2--;
  }
}