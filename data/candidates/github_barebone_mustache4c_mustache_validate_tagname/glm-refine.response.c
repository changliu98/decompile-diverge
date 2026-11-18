int __cdecl mustache_validate_tagname(const char *tagname, size_t size)
{
  size_t i;

  // Rule 1: A single dot is valid (often used for the implicit iterator `.`)
  if (size == 1 && tagname[0] == DOT)
    return SUCCESS;

  // Rule 2: Leading or trailing dots are invalid
  if (tagname[0] == DOT || tagname[size - 1] == DOT)
    return INVALID;

  // Rule 3: Iterate through the tag to check for invalid characters or sequences
  for (i = 0; i < size; ++i)
  {
    char c = tagname[i];

    // Disallow spaces, tabs, vertical tabs, and form feeds
    if (is_invalid_whitespace(c))
      return INVALID;

    // Disallow consecutive dots (e.g., "..")
    if (c == DOT && i + 1 < size && tagname[i + 1] == DOT)
      return INVALID;
  }

  return SUCCESS;
}