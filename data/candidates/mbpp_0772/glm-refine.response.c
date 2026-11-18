char *__cdecl func0(const char *input_str, int target_len)
{
  size_t input_len; 
  size_t current_len; 
  const char *token; 
  char *result; 
  char buffer[1000]; 
  const char *src_str; 
  int K; 

  src_str = input_str;
  K = target_len;
  
  // Copy the input string to a local buffer to avoid modifying the original
  strncpy(buffer, src_str, 0x3E8uLL);
  buffer[999] = 0;
  
  input_len = strlen(src_str);
  result = (char *)malloc(input_len + 1);
  if ( !result )
  {
    perror("malloc failed");
    exit(1);
  }
  *result = 0;
  
  // Tokenize the string by spaces and filter out words of length K
  for ( token = strtok(buffer, " "); token; token = strtok(0LL, " ") )
  {
    if ( strlen(token) != K )
    {
      strcat(result, token);
      strcat(result, " ");
    }
  }
  
  // Remove the trailing space if any tokens were appended
  current_len = strlen(result);
  if ( current_len && result[current_len - 1] == ' ' )
    result[current_len - 1] = 0;
    
  return result;
}