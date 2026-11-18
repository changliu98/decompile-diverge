void array_are_reference_type(int *a)
{
  int tmp = *a;
  *a = *(a + 1);
  *(a + 1) = tmp;
}