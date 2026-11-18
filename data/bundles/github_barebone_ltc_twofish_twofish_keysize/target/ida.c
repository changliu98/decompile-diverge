int __cdecl twofish_keysize(int *keysize)
{
  if ( !keysize )
    crypt_argchk("keysize", "./func.c", 695);
  if ( *keysize < 16 )
    return 3;
  if ( *keysize >= 24 )
  {
    if ( *keysize >= 32 )
      *keysize = 32;
    else
      *keysize = 24;
    return 0;
  }
  else
  {
    *keysize = 16;
    return 0;
  }
}