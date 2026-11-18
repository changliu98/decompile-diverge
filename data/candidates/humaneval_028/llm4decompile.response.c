char *func0(char **strings, int count)
{
 int i;
 int length = 0;
 for (i = 0; i < count; i++)
  length += strlen(strings[i]);

 char *result = malloc((size_t)(length + 1));
 if (result == NULL)
  return NULL;

 result[0] = '\0';
 for (i = 0; i < count; i++)
  strcat(result, strings[i]);

 return result;
}