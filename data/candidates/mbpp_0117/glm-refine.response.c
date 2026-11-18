Global buffer to store the result

char *__cdecl func0(char **test_list, int size)
{
  double first;
  double second;
  char temp[100];
  int i;

  strcpy(func0_res, "[");
  for (i = 0; i < size; i += 2)
  {
    first = atof(test_list[i]);
    second = atof(test_list[i + 1]);
    snprintf(temp, sizeof(temp), "(%.2f, %.2f)", first, second);
    strcat(func0_res, temp);
    
    if (i < size - 2)
      strcat(func0_res, ", ");
  }
  strcat(func0_res, "]");
  return func0_res;
}