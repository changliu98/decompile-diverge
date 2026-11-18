char *__cdecl func0(char **test_list, int size)
{
  char reversed[100]; 
  int count = 0;

  // Iterate over all elements in the list
  for (int idx = 0; idx < size; ++idx)
  {
    // Reverse the string at the current index 'idx'
    int len = strlen(test_list[idx]);
    for (int i = 0; i < len; ++i)
      reversed[i] = test_list[idx][len - 1 - i];
    reversed[len] = '\0';

    // Compare this reversed string against all strings 
    // from the current index 'idx' to the end of the list
    for (int idxn = idx; idxn < size; ++idxn)
    {
      if (strcmp(test_list[idxn], reversed) == 0)
        ++count;
    }
  }

  sprintf(func0_result, "%d", count);
  return func0_result;
}