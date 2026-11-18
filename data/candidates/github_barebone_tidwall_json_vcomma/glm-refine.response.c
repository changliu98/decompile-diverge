int64_t __cdecl vcomma(const uint8_t *json, int64_t len, int64_t i, uint8_t end)
{
  int64_t pos = i;
  uint8_t ch;

  // If we are already at the end of the string, return an error
  if (pos == len)
    return -(pos + 1);

  // Quick check: if the current character is a comma, we're done
  if (json[pos] == ',')
    return pos;

  // Skip over any whitespace characters
  while (1)
  {
    ch = json[pos];
    
    // Check if the character is NOT a whitespace character
    // (ASCII 9='\t', 10='\n', 13='\r', 32=' ')
    if (ch != '\t' && ch != '\n' && ch != '\r' && ch != ' ')
      break;

    // Move to the next character, abort if we run off the end
    if (++pos >= len)
      return -(pos + 1);
  }

  // After skipping whitespace, check if we found a comma
  if (ch == ',')
    return pos;

  // Otherwise, check if we found the specified 'end' delimiter
  if (ch == end)
    return pos;

  // If it's neither a comma nor the end delimiter, return an error
  return -(pos + 1);
}