int stb_combinations(int n, int t, int ***combinations)
{
   int *c, **comb;
   int i,j,x;
   int count=0;
   int rowsize;

   c = (int *) calloc(t+3, sizeof(int));

   rowsize = (int) (stb_factorial(n) / (stb_factorial(t) * stb_factorial(n-t)));

   comb = stb_allocmat(rowsize, t, sizeof(int));

   for (i=1; i <= t; ++i)
      c[i] = i-1;
   c[t+1] = n;
   c[t+2] = 0;

   for(;;) {
      stb_visit(c, t, &comb, count++);
      for(;;) {
         for(j=t; j > 0; --j)
            if (c[j] < j) break;
         if (j == 0) break;
         c[j]++;
         for(i=j+1; i <= t; ++i)
            c[i] = c[i-1]+1;
         stb_visit(c, t, &comb, count++);
      }
      if (c[1] + 1 < c[2]) {
         c[1]++;
         stb_visit(c, t, &comb, count++);
         continue;
      }
      j=2;
      c[1] = 0;
      while (c[j+1] == c[j]+1) {
         c[j++] -= 1;
      }
      if (j > t) break;
      c[j]++;
   }

   *combinations = comb;

   free(c);

   return rowsize;
}