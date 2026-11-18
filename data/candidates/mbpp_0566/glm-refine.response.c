int __cdecl func0(int n)
{
  if (n)
  {
    // Recursive step: sum the digits of the quotient (n / 10) 
    // and add the remainder (n % 10), which represents the last digit.
    return func0(n / 10) + (n % 10);
  }
  else
  {
    // Base case: when n becomes 0, there are no more digits to add.
    return 0;
  }
}