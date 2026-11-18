int keysize(int *keysize)
{
  if (keysize == ((void *)0))
    crypt_argchk("keysize", "./func.c", 695);
  if (*keysize < 16)
    return (3);
  if (*keysize < 24)
    *keysize = 16;
  else if (*keysize < 32)
    *keysize = 24;
  else
    *keysize = 32;
  return (0);
}