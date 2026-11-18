// Copies the string from 'word' to 'result' and returns 'result'
char * func0(char *source_string, char *destination_string)
{
  // Copy the content of 'word' to 'result'
  strcpy(destination_string, source_string);
  // Return the pointer to 'result'
  return destination_string;
}