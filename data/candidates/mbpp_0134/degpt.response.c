char * func0(int *arr,int n,int p)
{
  int totalSum = 0; // Initialize sum variable to zero
  for (int i = 0; i < n; i++) {
    totalSum += arr[i]; // Calculate the sum of all elements in the array
  }
  if (p == 1 && totalSum % 2 == 0) {
    return "ODD"; // If p is 1 and sum is even, return "ODD"
  }
  return "EVEN"; // Otherwise, return "EVEN"
}