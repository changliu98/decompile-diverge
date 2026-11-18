int create_encoding(char *encoding, char *decoding)
{
 int error = 0;
 int i;
 unsigned short positions[256];
 for (i = 0; i < 256; i++)
  positions[i] = 0xffff;

 for (i = 0; i < 256; i++) {
  int pos = decoding[i];
  int old_pos = positions[pos];

  if (old_pos != 0xffff) {
   error = 1;
  } else {
   positions[pos] = i;
  }
 }

 for (i = 0; i < 256; i++) {
  encoding[i] = positions[i] & 0xff;
 }

 return error ? -1 : 0;
}