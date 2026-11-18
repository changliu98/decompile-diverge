int __cdecl func0(int n)
{
  // If the input is even, print an error message and return -1
  if (n % 2 == 0)
  {
    printf("Invalid Input\n");
    return -1;
  }

  int count = 0;
  int sum = 0;
  int current_val = n;

  // Iterate through all odd numbers from n down to 1
  while (current_val >= 1)
  {
    ++count;
    sum += current_val;
    current_val -= 2;
  }

  // Return the average of the odd numbers
  return sum / count;
}