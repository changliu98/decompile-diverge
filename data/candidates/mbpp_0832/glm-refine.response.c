int __cdecl func0(const char *input)
{
  char temp[256];
  int max = 0;
  int index = 0;
  int current_num;
  int i;

  // Iterate through the string until the null terminator
  for (i = 0; input[i] != '\0'; ++i)
  {
    // Check if the character is a decimal digit ('0' to '9')
    if (input[i] >= '0' && input[i] <= '9')
    {
      temp[index++] = input[i];
    }
    else
    {
      // If we encounter a non-digit and we have buffered digits
      if (index > 0)
      {
        temp[index] = '\0';
        current_num = atoi(temp);
        
        if (current_num > max)
        {
          max = current_num;
        }
        index = 0;
      }
    }
  }

  // Process any remaining digits at the end of the string
  if (index > 0)
  {
    temp[index] = '\0';
    current_num = atoi(temp);
    
    if (current_num > max)
    {
      return current_num;
    }
  }

  return max;
}