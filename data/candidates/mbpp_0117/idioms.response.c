char *func0(char **list, int size)
{
  int i;
  char temp[100];
  list = test_list;
  size = list_size;
  strcpy(res, "[");
  for (i = 0; i < size; i += 2)
  {
    snprintf(temp, sizeof temp, "(%.2f, %.2f)", atof(list[i]), atof(list[i + 1]));
    strcat(res, temp);
    if (i < size - 2)
      strcat(res, ", ");
  }
  strcat(res, "]");
  return res;
}