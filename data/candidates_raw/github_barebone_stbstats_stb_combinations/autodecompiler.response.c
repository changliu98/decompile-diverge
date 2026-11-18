int stb_n_choose_k(int n, int k, int **out)
{
   int *perm = (int *) calloc(n+3, sizeof(perm[0]));
   int i,j,c=0,nck;
   int **list = stb_allocmat(nck = (int) (stb_factorial(n) / (stb_factorial(k) * stb_factorial(n-k))), k, sizeof(list[0][0]));

   for (i=1; i <= k; ++i)
      perm[i] = i-1;

   perm[k+1] = n;
   perm[k+2] = 0;

   i=k;
   while (1) {
      stb_visit(perm,k,list,c++);
      while (i > 0 && perm[i]+1 == perm[i+1]) --i;
      if (i > 0) {
         j = perm[i]+1;
         while (i < k) {
            perm[i] = j;
            ++i;
            stb_visit(perm,k,list,c++);
         }
      } else {
         while (perm[1]+1 < perm[2]) {
            ++perm[1];
            stb_visit(perm,k,list,c++);
            while (i > 0 && perm[i]+1 == perm[i+1]) --i;
            if (i > 0) {
               j = perm[i]+1;
               while (i < k) {
                  perm[i] = j;
                  ++i;
                  stb_visit(perm,k,list,c++);
               }
            }
         }
         perm[1] = 2;
         perm[2] = 1 + perm[1];
         i=2;
         while (perm[i] == perm[i+1]-1) {
            ++i;
            perm[i] = 1 + perm[i-1];
         }
         if (i >= k) break;
         perm[i] = j+1;
         i=i-1;
      }
   }

   *out = list;
   free(perm);
   return nck;
}