int func0(int *array, int length)
{
 int *copy = malloc(length * sizeof(int));
 int i, j, temp;
 char is_consecutive = 1;

 for (i = 0; i < length; i++)
 {
  *(copy + i) = array[i];
 }

 for (i = 0; i < length; i++)
 {
  for (j = i + 1; j < length; j++)
  {
   if (*(copy + i) > *(copy + j))
   {
    temp = *(copy + i);
    *(copy + i) = *(copy + j);
    *(copy + j) = temp;
   }
  }
 }

 for (i = 1; i < length; i++)
 {
  if (*(copy + i) != *(copy + i - 1) + 1)
  {
   is_consecutive = 0;
   break;
  }
 }

 free(copy);

 return is_consecutive;
}