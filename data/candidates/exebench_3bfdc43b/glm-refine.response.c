void __cdecl norm(int *hi, int *lo, int base)
{
  int borrow;
  int carry;

  // Handle negative values in the lower part by borrowing from the higher part.
  // This ensures the lower part becomes non-negative.
  if ( *lo < 0 )
  {
    // Calculate the number of 'base' units needed to make *lo non-negative.
    // The (-*lo - 1) / base + 1 pattern is a standard C idiom for ceiling division of a negative number.
    borrow = (-*lo - 1) / base + 1;
    *hi -= borrow;
    *lo += base * borrow;
  }

  // Handle values in the lower part that exceed or equal the base by carrying over to the higher part.
  // This ensures the lower part is strictly less than the base.
  if ( *lo >= base )
  {
    carry = *lo / base;
    *hi += carry;
    *lo %= base; // Equivalent to: *lo -= base * carry;
  }
}