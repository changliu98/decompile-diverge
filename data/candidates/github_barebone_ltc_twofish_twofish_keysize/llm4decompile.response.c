int
twofish_keysize(int *keysize)
{
 if (keysize == NULL)
  crypt_argchk("keysize", "./func.c", 695);

 if (*keysize < 16)
  return (3);
 if (*keysize < 24) {
  *keysize = 16;
  return (0);
 }
 if (*keysize < 32) {
  *keysize = 24;
  return (0);
 }
 *keysize = 32;
 return (0);
}