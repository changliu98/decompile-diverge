#include <limits.h>

// Recursive function to find the minimum number of coins required to make a given value
int __cdecl minCoins(int *coins, int num_coins, int amount)
{
  // Base case: If the amount is 0, 0 coins are needed
  if (amount == 0)
    return 0;

  // Initialize the minimum coins needed to INT_MAX (representing an impossible state)
  int min_coins_needed = INT_MAX;

  // Try every coin of different denominations
  for (int i = 0; i < num_coins; ++i)
  {
    // Check if the coin value does not exceed the remaining amount
    if (coins[i] <= amount)
    {
      // Recursively compute the minimum coins needed for the reduced amount
      int sub_res = minCoins(coins, num_coins, amount - coins[i]);

      // If the sub-problem can be solved, update the minimum if a better solution is found
      if (sub_res != INT_MAX && sub_res + 1 < min_coins_needed)
        min_coins_needed = sub_res + 1;
    }
  }

  return min_coins_needed;
}