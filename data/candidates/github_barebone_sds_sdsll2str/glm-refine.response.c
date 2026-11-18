int __cdecl sdsll2str(char *s, __int64 value)
{
  char *start = s;
  unsigned __int64 v;
  char *p = s;
  int length;
  char *pa;
  char aux;

  // Convert the integer to its absolute value.
  // Handle the edge case for INT64_MIN explicitly to avoid overflow.
  if (value >= 0)
  {
    v = value;
  }
  else if (value == 0x8000000000000000LL)
  {
    v = 0x8000000000000000LL;
  }
  else
  {
    v = -value;
  }

  // Write digits in reverse order (least significant digit first)
  do
  {
    *p++ = (v % 10) + '0';
    v /= 10;
  }
  while (v);

  // Append the minus sign if the original number was negative
  if (value < 0)
  {
    *p++ = '-';
  }

  // Calculate the length of the generated string and null-terminate it
  length = (int)(p - s);
  *p = '\0';

  // Reverse the string in-place to correct the digit order
  for (pa = p - 1; start < pa; --pa)
  {
    aux = *start;
    *start = *pa;
    *pa = aux;
    ++start;
  }

  return length;
}