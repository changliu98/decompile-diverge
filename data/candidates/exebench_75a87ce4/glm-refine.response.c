void __cdecl f(char *src, char *dst)
{
  // Copies the first character of the source string/buffer 
  // to the second byte of the destination string/buffer.
  dst[1] = src[0];
}