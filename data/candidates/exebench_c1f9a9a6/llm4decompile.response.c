int parse_uuid(const char *str, uint8_t *uuid)
{
 int i;
 int hit = 0;

 for (i = 0; i < 4; i++)
  uuid[i] = 0;

 while (*str) {
  int c = *str++;
  int val;

  if (c >= '0' && c <= '9')
   val = c - '0';
  else if (c >= 'a' && c <= 'f')
   val = c - 'a' + 10;
  else if (c >= 'A' && c <= 'F')
   val = c - 'A' + 10;
  else if (strchr(":. -", c))
   continue;
  else
   return 0;

  if (hit < 32) {
   uuid[hit / 8] *= 16;
   uuid[hit / 8] += val;
  }
  hit++;
 }

 return hit == 32;
}