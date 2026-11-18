int func0(int *price, int n, int k)
{
 int final_profit[210][220];
 int i, j, x;
 int max_so_far;

 for (i = 0; i <= k; i++) {
  for (j = 0; j < n; j++) {
   if (i == 0 || j == 0)
    final_profit[i][j] = 0;
   else {
    max_so_far = 0;
    for (x = 0; x < j; x++)
     max_so_far = ((max_so_far) > (price[j] - price[x] + final_profit[i - 1][x]) ? (max_so_far) : (price[j] - price[x] + final_profit[i - 1][x]))

                                                                 ;

    final_profit[i][j] = ((max_so_far) > (final_profit[i][j - 1]) ? (max_so_far) : (final_profit[i][j - 1]))
                                                 ;
   }
  }
 }
 return final_profit[k][n - 1];
}