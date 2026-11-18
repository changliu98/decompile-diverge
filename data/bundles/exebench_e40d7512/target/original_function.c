static char *
scnline(int key, char *p, int c)
{
 int scnwidth;

 for (scnwidth = 8; --scnwidth;) {
  key <<= 1;
  *p++ = key & 0200 ? c : ' ';
 }
 return (p);
}