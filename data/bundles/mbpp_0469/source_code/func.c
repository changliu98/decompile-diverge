

#include <stdio.h>

#include <assert.h>





int func0(int price[], int n, int k) {
  int final_profit[k + 1][n];
  for (int i = 0; i <= k; i++) {
    for (int j = 0; j < n; j++) {
      if (i == 0 || j == 0) {
        final_profit[i][j] = 0;
      } else {
        int max_so_far = 0;
        for (int x = 0; x < j; x++) {
          int curr_price = price[j] - price[x] + final_profit[i - 1][x];
          if (max_so_far < curr_price) {
            max_so_far = curr_price;
          }
        }
        final_profit[i][j] = (final_profit[i][j - 1] > max_so_far)
                                 ? final_profit[i][j - 1]
                                 : max_so_far;
      }
    }
  }
  return final_profit[k][n - 1];
}
