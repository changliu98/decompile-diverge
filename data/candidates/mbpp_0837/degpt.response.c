int func0(int n)
{
  int index;
  int total_cube_sum = 0;
  
  // Iterate from 0 to n-1
  for (index = 0; index < n; index++) {
    // Calculate the cube of the (2*i + 1)-th odd number and add to sum
    total_cube_sum += (index * 2 + 1) * (index * 2 + 1) * (index * 2 + 1);
  }
  return total_cube_sum;
}