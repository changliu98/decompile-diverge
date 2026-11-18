// Converts snake_case string to CamelCase string
// Input: word - null-terminated string in snake_case format
// Input: output - buffer to store the resulting CamelCase string
// Returns: pointer to the output buffer
char * func0(char *snake_case_input,char *camel_case_output)
{
  int input_index = 0, output_index = 0;
  bool should_capitalize_next = true;
  // Iterate through each character of the input word until null terminator
  while (snake_case_input[input_index] != '\0') {
    // If current character is underscore, set flag to capitalize next alphabetic character
    if (snake_case_input[input_index] == '_') {
      should_capitalize_next = true;
    } else {
      // If capitalize_next flag is set, convert character to uppercase
      if (should_capitalize_next) {
        camel_case_output[output_index] = toupper((int)snake_case_input[input_index]);
        should_capitalize_next = false;
      } else {
        // Otherwise, copy character as-is
        camel_case_output[output_index] = snake_case_input[input_index];
      }
      // Move to next position in output buffer
      output_index++;
    }
    // Move to next character in input word
    input_index++;
  }
  // Null-terminate the output string
  camel_case_output[output_index] = '\0';
  return camel_case_output;
}