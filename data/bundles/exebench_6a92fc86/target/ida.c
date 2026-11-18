int __cdecl parse_width(const char *str, int *len_p)
{
  int len; // [rsp+4h] [rbp-18h]
  int val; // [rsp+8h] [rbp-14h]

  val = 0;
  for ( len = 0; str[len] && str[len] >= 48 && str[len] <= 57; ++len )
    val = str[len] - 48 + 10 * val;
  *len_p = len;
  return val;
}