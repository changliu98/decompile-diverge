int __cdecl func0(const char *str)
{
  int count = 0;
  int len = strlen(str);

  // Handle empty or single-character strings safely
  if (len < 2) {
    return 0;
  }

  // Check the first character
  if (!is_vowel(str[0]) && is_vowel(str[1])) {
    ++count;
  }

  // Check the middle characters
  for (int i = 1; i < len - 1; ++i) {
    if (!is_vowel(str[i]) && (is_vowel(str[i - 1]) || is_vowel(str[i + 1]))) {
      ++count;
    }
  }

  // Check the last character
  if (!is_vowel(str[len - 1]) && is_vowel(str[len - 2])) {
    ++count;
  }

  return count;
}