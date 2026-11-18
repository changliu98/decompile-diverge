void __cdecl sort_three(int *v1, int *v2, int *v3)
{
  int temp;

  // Ensure the smallest value is in v1
  if (*v1 > *v2)
  {
    temp = *v2;
    *v2 = *v1;
    *v1 = temp;
  }
  if (*v1 > *v3)
  {
    temp = *v3;
    *v3 = *v1;
    *v1 = temp;
  }

  // Ensure the remaining two are sorted
  if (*v2 > *v3)
  {
    temp = *v2;
    *v2 = *v3;
    *v3 = temp;
  }
}