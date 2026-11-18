
int parse_uuid(char *str, int uuid[4])
{
 int hit = 0;
 int i;
 char c;
 for (i=0; i<4; i++) uuid[i]=0;

 while ((c= *str++)) {
  int n;
  if (c>='0' && c<='9')
   n = c-'0';
  else if (c>='a' && c <= 'f')
   n = 10 + c - 'a';
  else if (c>='A' && c <= 'F')
   n = 10 + c - 'A';
  else if (strchr(":. -", c))
   continue;
  else return 0;

  if (hit<32) {
   uuid[hit/8] <<= 4;
   uuid[hit/8] += n;
  }
  hit++;
 }
 if (hit == 32)
  return 1;
 return 0;
}
