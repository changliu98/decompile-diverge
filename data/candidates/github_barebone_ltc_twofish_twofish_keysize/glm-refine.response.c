int __cdecl twofish_keysize(int *keysize)
{
  if (!keysize)
    crypt_argchk("keysize", "./func.c", 695);

  if (*keysize < 16)
    return 3;

  if (*keysize >= 32) {
    *keysize = 32;
  } else if (*keysize >= 24) {
    *keysize = 24;
  } else {
    *keysize = 16;
  }

  return 0;
}