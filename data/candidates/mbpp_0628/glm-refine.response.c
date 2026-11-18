char *__cdecl func0(char *string)
{
  int length; 
  int space_count; 
  int new_length; 
  int old_index; 
  int new_index; 
  char new_string[1000]; 
  char *result; 

  space_count = 0;
  length = strlen(string);
  
  // Count the number of spaces in the original string
  for (int i = 0; i < length; ++i)
  {
    if (string[i] == ' ')
      ++space_count;
  }
  
  // Calculate the new length after replacing ' ' with "%20"
  new_length = 2 * space_count + length;
  
  // Prevent buffer overflow on the local 1000-byte array
  if (new_length > 1000)
    return "";
    
  new_index = new_length - 1;
  new_string[new_length] = '\0';
  
  // Iterate backwards to replace spaces with "%20"
  for (old_index = length - 1; old_index >= 0; --old_index)
  {
    if (string[old_index] == ' ')
    {
      new_string[new_index] = '0';
      new_string[new_index - 1] = '2';
      new_string[new_index - 2] = '%';
      new_index -= 3;
    }
    else
    {
      new_string[new_index--] = string[old_index];
    }
  }
  
  // Allocate exact required memory and copy the modified string
  result = (char *)malloc(new_length + 1);
  strcpy(result, new_string);
  
  return result;
}