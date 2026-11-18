// Replaces all occurrences of origc with newc in the null-terminated string str
void char_replace(char *text, char target_char, char replacement_char)
{
  // Iterate through the string until the null terminator is reached
  while (*text != '\0') {
    // If the current character matches origc, replace it with newc
    if (*text == target_char) {
      *text = replacement_char;
    }
    // Move to the next character in the string
    text++;
  }
}