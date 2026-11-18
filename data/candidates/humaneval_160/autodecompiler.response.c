int func0(char ** tokens, int * numbers, int no_t, int no_n)
{
 int * n = (int *)malloc(no_n * sizeof(int));
 int * positions = (int *)malloc(no_n * sizeof(int));

 int result, i;

 for (i = 0; i < no_n; i++)
 {
  n[i] = numbers[i];
  positions[i] = i;
 }

 int j;
 for (i = 0; i < no_t; i++)
 {
  if (strcmp(tokens[i], "**") == 0)
  {
   while (positions[i] != positions[positions[i]])
   {
    positions[i] = positions[positions[i]];
   }
   while (positions[i + 1] != positions[positions[i + 1]])
   {
    positions[i + 1] = positions[positions[i + 1]];
   }
   n[positions[i]] = (int)pow((double)n[positions[i]], (double)n[positions[i + 1]]);
   positions[i + 1] = positions[i];
  }
  else
  {
   continue;
  }
 }

 for (i = 0; i < no_t; i++)
 {
  if (strcmp(tokens[i], "*") == 0 || strcmp(tokens[i], "//") == 0)
  {
   while (positions[i] != positions[positions[i]])
   {
    positions[i] = positions[positions[i]];
   }
   while (positions[i + 1] != positions[positions[i + 1]])
   {
    positions[i + 1] = positions[positions[i + 1]];
   }
   if (strcmp(tokens[i], "*") == 0)
   {
    n[positions[i]] = n[positions[i]] * n[positions[i + 1]];
   }
   else
   {
    n[positions[i]] = n[positions[i]] / n[positions[i + 1]];
   }
   positions[i + 1] = positions[i];
  }
  else
  {
   continue;
  }
 }

 for (i = 0; i < no_t; i++)
 {
  if (strcmp(tokens[i], "+") == 0 || strcmp(tokens[i], "-") == 0)
  {
   while (positions[i] != positions[positions[i]])
   {
    positions[i] = positions[positions[i]];
   }
   while (positions[i + 1] != positions[positions[i + 1]])
   {
    positions[i + 1] = positions[positions[i + 1]];
   }
   if (strcmp(tokens[i], "+") == 0)
   {
    n[positions[i]] = n[positions[i]] + n[positions[i + 1]];
   }
   else
   {
    n[positions[i]] = n[positions[i]] - n[positions[i + 1]];
   }
   positions[i + 1] = positions[i];
  }
  else
  {
   continue;
  }
 }

 result = n[0];

 free(n);
 free(positions);

 return result;
}