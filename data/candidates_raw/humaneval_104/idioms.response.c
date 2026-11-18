void even_digits(int *array, int size, int **out, int *out_size)
{
  int i;
  int j;
  int temp;
  int num;
  int has_even_digit;
  int is_even;
  *out = (int *)malloc(size * sizeof(int));
  *out_size = 0;
  for (i = 0; i < size; i++)
  {
    num = array[i];
    has_even_digit = (num == 0);
    do
    {
      is_even = 0;
      if (num > 0)
      {
        is_even = ~has_even_digit;
      }
      if (is_even % 2 == 0)
      {
        if (num % 2 == 0)
        {
          has_even_digit = 1;
        }
        num = num / 10;
      }
      else
      {
        if (has_even_digit % 2 == 0)
        {
          (*out)[(*out_size)] = array[i];
          (*out_size)++;
        }
        break;
      }
    } while (num > 0);
  }
  for (i = 0; i < *out_size - 1; i++)
  {
    for (j = 0; j < *out_size - i - 1; j++)
    {
      if ((*out)[j] > (*out)[j + 1])
      {
        temp = (*out)[j];
        (*out)[j] = (*out)[j + 1];
        (*out)[j + 1] = temp;
      }
    }
  }
}