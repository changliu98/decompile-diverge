// Checks if the given character 'c' is a lowercase ASCII letter.
// Returns 1 if 'c' is between 'a' (0x61) and 'z' (0x7a), otherwise returns 0.
int Q_islower(int char_code)
{
  return (char_code >= 0x61 && char_code <= 0x7a);
}