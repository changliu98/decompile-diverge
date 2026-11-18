int twofish_keysize(int *klen)
{
   int ret;

   if (klen == NULL) {
      crypt_argchk("keysize", "./func.c", 695);
   }

   while (*klen < 16) {
      *klen = 3;
      return 3;
   }

   if (*klen < 24) {
      *klen = 16;
      ret = 0;
   } else if (*klen < 32) {
      *klen = 24;
      ret = 0;
   } else {
      *klen = 32;
      ret = 0;
   }


   return ret;
}