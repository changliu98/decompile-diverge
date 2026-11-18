void to_upper(char *chr)
{
  if (*chr >= 'a' && *chr <= 'z')
    *chr = *chr - 'a' + 'A';
}