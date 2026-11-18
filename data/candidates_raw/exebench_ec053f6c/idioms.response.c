void swap(int *array)
{
  char temp = array[0];
  array[0] = array[3];
  array[3] = temp;
  temp = array[1];
  array[1] = array[2];
  array[2] = temp;
}