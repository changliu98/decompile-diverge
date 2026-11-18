int *__cdecl func0(int *numbers, int size, int *new_size)
{
  int *out = (int *)malloc(4LL * size);
  int *has1 = (int *)calloc(size, 4uLL);
  int *has2 = (int *)calloc(size, 4uLL);
  
  int has1_count = 0;
  int has2_count = 0;
  int out_count = 0;

  // First pass: Categorize numbers based on their frequency
  for (int i = 0; i < size; ++i)
  {
    int num = numbers[i];
    int in_has2 = 0;
    
    for (int j = 0; j < has2_count; ++j)
    {
      if (has2[j] == num)
      {
        in_has2 = 1;
        break;
      }
    }
    
    if (!in_has2)
    {
      int in_has1 = 0;
      for (int j = 0; j < has1_count; ++j)
      {
        if (has1[j] == num)
        {
          in_has1 = 1;
          break;
        }
      }
      
      if (in_has1)
      {
        // Number has been seen once before; promote it to has2
        has2[has2_count++] = num;
      }
      else
      {
        // First time seeing this number; add to has1
        has1[has1_count++] = num;
      }
    }
  }

  // Second pass: Filter out numbers that appeared more than once
  for (int i = 0; i < size; ++i)
  {
    int num = numbers[i];
    int is_duplicate = 0;
    
    for (int j = 0; j < has2_count; ++j)
    {
      if (has2[j] == num)
      {
        is_duplicate = 1;
        break;
      }
    }
    
    if (!is_duplicate)
    {
      out[out_count++] = num;
    }
  }

  *new_size = out_count;
  
  free(has1);
  free(has2);
  
  return out;
}