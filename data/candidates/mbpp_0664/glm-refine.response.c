int __cdecl func0(int n)
{
  // If n is odd, print an error message and return -1
  if (n % 2 != 0)
  {
    printf("Invalid Input\n");
    return -1;
  }

  int sum = 0;
  int count = 0;
  int current_val = n;

  // Iteratively subtract 2 from n down to 2, accumulating the sum and count
  while (current_val >= 2)
  {
    ++count;
    sum += current_val;
    current_val -= 2;
  }

  // Calculate and return the average
  return sum / count;
}