int twofish_keysize(int *key_size)
{
  // Check if the keysize pointer is valid
  if (key_size == NULL) {
    crypt_argchk("keysize","./func.c",0x2b7);
  }
  // If the key size is less than 16 bytes, return an error
  if (*key_size < 0x10) {
    return 3;
  }
  // If the key size is less than 24 bytes, adjust it to 16 bytes
  else if (*key_size < 0x18) {
    *key_size = 0x10;
  }
  // If the key size is less than 32 bytes, adjust it to 24 bytes
  else if (*key_size < 0x20) {
    *key_size = 0x18;
  }
  // Otherwise, adjust the key size to 32 bytes
  else {
    *key_size = 0x20;
  }
  // Return success
  return 0;
}