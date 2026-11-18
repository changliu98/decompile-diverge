void makeipt(int m, int *list)
{
   int n, j, k, i, is, id, l;
   list[2] = 0;
   list[3] = 16;
   n = 2;
   l = m;
   while (l > 32) {
      is = 2 * n;
      id = 8 * n;
      for (j = n; j < is; j++) {
         k = 4 * list[j];
         list[j + n] = k;
         list[j + is] = k + id;
      }
      n = is;
      l = l >> 2;
   }
}