unsigned __int64 __cdecl func0(int n)
{
  unsigned __int64 **bell_triangle;
  unsigned __int64 result;
  int row, col;

  // Allocate memory for the 2D Bell triangle
  bell_triangle = (unsigned __int64 **)malloc(sizeof(unsigned __int64 *) * (n + 1));
  for (row = 0; row <= n; ++row)
  {
    bell_triangle[row] = (unsigned __int64 *)malloc(sizeof(unsigned __int64) * (n + 1));
    for (col = 0; col <= n; ++col)
      bell_triangle[row][col] = 0;
  }

  // Base case
  bell_triangle[0][0] = 1;

  // Build the Bell triangle
  for (row = 1; row <= n; ++row)
  {
    // The first element of each row is the last element of the previous row
    bell_triangle[row][0] = bell_triangle[row - 1][row - 1];
    
    // Each subsequent element is the sum of the element to its left and the element diagonally above to the left
    for (col = 1; col <= row; ++col)
      bell_triangle[row][col] = bell_triangle[row][col - 1] + bell_triangle[row - 1][col - 1];
  }

  // The n-th Bell number is the first element of the n-th row
  result = bell_triangle[n][0];

  // Free allocated memory
  for (row = 0; row <= n; ++row)
    free(bell_triangle[row]);
  free(bell_triangle);

  return result;
}