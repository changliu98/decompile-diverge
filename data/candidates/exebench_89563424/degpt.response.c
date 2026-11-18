void f(int *arr)
{
  // Assign the value pointed to by p to the third element of the array
  arr[2] = *arr;
  // Assign the second element of the array to the fourth element of the array
  arr[3] = arr[1];
}