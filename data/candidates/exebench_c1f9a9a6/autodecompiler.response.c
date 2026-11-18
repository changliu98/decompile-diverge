int parse_uuid(char *hex, unsigned char bin[8])
{
 char c;
 int i, n, ret, len = 0;

 for (i = 0; i < 8 / 2; i++)
  bin[i] = 0;

 while (1) {
  c = *hex++;
  if (!c)
   break;
  if ((c >= '0') && (c <= '9'))
   n = c - '0';
  else if ((c >= 'a') && (c <= 'f'))
   n = c - 'a' + 10;
  else if ((c >= 'A') && (c <= 'F'))
   n = c - 'A' + 10;
  else if (strchr(":. -", c))
   continue;
  else
   return 0;
  if (len < 8 * 4) {
   bin[len / 8] <<= 4;
   bin[len / 8] += n;
  }
  len++;
 }

 if (len == 8 * 4)
  ret = 1;
 else
  ret = 0;

 return ret;
}