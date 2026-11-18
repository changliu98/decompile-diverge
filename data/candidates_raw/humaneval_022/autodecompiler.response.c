static int *func0(char *s, int *n)
{
 char *p, *l;
 int i, j, k, m;
 static int func0_out[100];

 for (i = 0, p = s; *p != '\0'; p++) {
  while (((*p) && (*___ctype_b_loc ()[(int)((*p))] & (unsigned short int)0x0800)) || ((*p) == '-')) p++;
  if (*p == '\0') break;
  j = strtol(p, &l, 10);
  if ((p != l) && ((*l == ',') || (*l == '\0'))) {
   func0_out[i++] = j;
  } else {
   while (((*l) && (*l != ','))) l++;
  }
  p = l;
 }

 *n = i;

 return func0_out;
}