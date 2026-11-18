char *scnline(int key, char *p, int c)
{
 int i;

 for (i = 0; i < 8; i++) {
  key = key << 1;
  *p = (key & 0x80) ? c : ' ';
  p++;
 }
 return p;
}