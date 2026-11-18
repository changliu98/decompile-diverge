const char *__cdecl func0(const char *numbers)
{
  char current[6]; 
  int k, j, i;
  int index = 0;
  const char *numto[10];
  int count[10] = {0};
  const char *p = numbers;

  // Initialize the array of number strings (presumably "zero", "one", ..., "nine")
  memcpy(numto, &off_3D90, sizeof(numto));

  if (*p)
  {
    do
    {
      // Extract a word separated by spaces
      for (i = 0; ; ++i)
      {
        bool is_delimiter = (p[i] == ' ' || p[i] == '\0');
        if (is_delimiter)
          break;
        current[i] = p[i];
      }
      current[i] = '\0';

      // Find the extracted word in the numto array and increment its count
      for (j = 0; j < 10; ++j)
      {
        if (strcmp(current, numto[j]) == 0)
        {
          ++count[j];
          break;
        }
      }

      // Advance pointer past the word and the delimiter
      p += i + 1;
    }
    while (*(p - 1)); // Continue if the previous delimiter wasn't the null terminator
  }

  // Reconstruct the sorted output
  for (i = 0; i < 10; ++i)
  {
    for (j = 0; j < count[i]; ++j)
    {
      // Append the number string
      for (k = 0; numto[i][k]; ++k)
        func0_out[index++] = numto[i][k];
      
      // Append a space
      func0_out[index++] = ' ';
    }
  }

  // Null-terminate the output string
  if (index <= 0)
    func0_out[0] = '\0';
  else
    func0_out[index - 1] = '\0'; // Overwrite the trailing space with null terminator

  return func0_out;
}