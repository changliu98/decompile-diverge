void toup(char *chr_ptr)
{
  if (*chr_ptr >= 'a' && *chr_ptr <= 'z')
    *chr_ptr = *chr_ptr - 'a' + 'A';
}