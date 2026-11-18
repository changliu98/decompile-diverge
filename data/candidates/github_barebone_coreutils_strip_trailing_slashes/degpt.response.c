_Bool strip_trailing_slashes(char *filePath)
{
  // Get the last component of the file path
  char *lastComponent = last_component(filePath);
  
  // If the last component is empty, use the original file pointer
  if (*lastComponent == '\0') {
    lastComponent = filePath;
  }
  
  // Calculate the length of the base component
  size_t componentLength = base_len(lastComponent);
  
  // Save the character immediately following the base component
  char nextChar = lastComponent[componentLength];
  
  // Terminate the base component by placing a null terminator
  lastComponent[componentLength] = '\0';
  
  // Return true if there was a character after the base component (i.e., trailing slashes existed)
  return nextChar != '\0';
}