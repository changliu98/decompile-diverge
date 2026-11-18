void swap(int *one, int *two)
{
  int aux = *one;
  *one = *two;
  *two = aux;
}