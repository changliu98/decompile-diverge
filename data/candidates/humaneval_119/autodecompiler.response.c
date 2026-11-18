char *func0(char *g, char *h) {
 int i, n, m, p;
 char *c;
 p = 0;
 n = strlen(g);
 m = strlen(h);
 int ok = 1;

 for (i = 0; ; i++) {
  if (i >= n) {
   i = 0;
   break;
  }
  switch (g[i]) {
   case '(' : p++; break;
   case ')' : p--; break;
  }
  if (p < 0) ok = 0;
 }

 for (i = 0; ; i++) {
  if (i >= m) {
   i = 0;
   break;
  }
  switch (h[i]) {
   case '(' : p++; break;
   case ')' : p--; break;
  }
  if (p < 0) ok = 0;
 }

 if ((p == 0) && ok) c = "Y";
 else c = "N";

 p = 0;
 ok = 1;

 for (i = 0; ; i++) {
  if (i >= m) {
   i = 0;
   break;
  }
  switch (h[i]) {
   case '(' : p++; break;
   case ')' : p--; break;
  }
  if (p < 0) ok = 0;
 }

 for (i = 0; ; i++) {
  if (i >= n) {
   i = 0;
   break;
  }
  switch (g[i]) {
   case '(' : p++; break;
   case ')' : p--; break;
  }
  if (p < 0) ok = 0;
 }

 if ((p == 0) && ok) c = "Y";
 else c = "N";

 return c;
}