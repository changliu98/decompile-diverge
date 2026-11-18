void __cdecl MatrixM(int a[2][2], int b[2][2])
{
  // Temporary variables to store the new values for matrix 'a'
  // before overwriting its elements.
  int new_a01; // Corresponds to t2
  int new_a10; // Corresponds to t3
  int new_a11; // Corresponds to t4

  // Calculate the new matrix elements: a = (b * a) % 100
  new_a01 = (b[0][1] * a[0][1] + b[0][0] * a[0][0]) % 100;
  new_a10 = (b[1][0] * a[1][1] + b[0][0] * a[1][0]) % 100;
  new_a11 = (b[1][1] * a[1][1] + b[0][1] * a[1][0]) % 100;
  
  // Overwrite the original matrix 'a' with the calculated values
  a[0][0] = (b[1][0] * a[0][1] + b[0][0] * a[0][0]) % 100;
  a[0][1] = new_a01;
  a[1][0] = new_a10;
  a[1][1] = new_a11;
}