char *remove_spaces(char *str)
{
  size_t size = strlen(str);
  char *copy = (char *)malloc((size + 1) * sizeof(char));
  if (copy == NULL)
    {
      char *error_msg = "Error in remove_spaces";
      write(2, error_msg, strlen(error_msg));
      return (NULL);
    }
  size_t i;
  size_t j;
  char *tmp;
  tmp = copy;
  j = 0;
  for (i = 0; i < size; i++)
    {
      if (!((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short int) 256))
 tmp[j++] = str[i];
    }
  tmp[j] = '\0';
  return (copy);
}