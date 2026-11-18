char * base_name(char *name)
{
  char *base_name;
  size_t base_length;
  idx_t result_length;
  char *result_string;

  // Get the last component of the path (filename part)
  base_name = last_component(name);
  
  // If the last component is empty (e.g., path ends with '/'), use the full name
  if (*base_name == '\0') {
    result_length = base_len(name);
    base_name = name;
  }
  else {
    // Calculate the length of the base component
    base_length = base_len(base_name);
    // Determine if the base ends with '/', and adjust length accordingly
    result_length = (long)(int)(uint)(base_name[base_length] == '/') + base_length;
  }
  
  // Allocate memory for the result string (length + 1 for null terminator)
  result_string = ximalloc(result_length + 1);
  
  // Copy the base name to the destination buffer
  memcpy(result_string, base_name, result_length);
  
  // Null-terminate the destination string
  result_string[result_length] = '\0';
  
  // Return the newly allocated base name
  return result_string;
}