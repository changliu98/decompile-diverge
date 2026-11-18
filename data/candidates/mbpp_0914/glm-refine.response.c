// Checks if a string is an alternating 2-character sequence (e.g., "ababab").
// Returns true if the string alternates between two distinct characters, false otherwise.
bool __cdecl is_alternating_string(const char *s)
{
  size_t length = strlen(s);
  
  // Iterate through the string, comparing each character to the one 2 positions ahead.
  // If any pair differs, the alternating pattern is broken.
  for (size_t i = 0; i < length - 2; ++i)
  {
    if (s[i] != s[i + 2])
      return false;
  }
  
  // Finally, ensure the two alternating characters are not the exact same character.
  return s[0] != s[1];
}