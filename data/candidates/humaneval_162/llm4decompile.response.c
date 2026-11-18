char *
func0(const char *text)
{
 unsigned int crc;
 char *result;
 int len;

 len = strlen(text);
 if (len == 0)
  return strdup("None");

 crc = 0xffffffff;
 while (*text != 0) {
  crc ^= (unsigned char) *text++;
  for (len = 0; len < 8; len++)
   crc = crc & 1 ? (crc >> 1) ^ 0xedb88320 : crc >> 1;
 }
 crc ^= 0xffffffff;

 result = malloc(9);
 if (result == NULL)
  return NULL;
 sprintf(result, "%08X", crc);
 return result;
}