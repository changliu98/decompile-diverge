int twofish_keysize(int *keysize)

{
  int *keysize_local;
  int local_c;
  
  if (keysize == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
    crypt_argchk("keysize","./func.c",0x2b7);
  }
  if (*keysize < 0x10) {
    local_c = 3;
  }
  else if (*keysize < 0x18) {
    *keysize = 0x10;
    local_c = 0;
  }
  else if (*keysize < 0x20) {
    *keysize = 0x18;
    local_c = 0;
  }
  else {
    *keysize = 0x20;
    local_c = 0;
  }
  return local_c;
}