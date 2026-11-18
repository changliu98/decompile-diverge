char *__cdecl func0(const char *str)
{
  // Compares the first character with the last character of the string.
  // Note: The (int) cast is preserved to match the original assembly's 
  // signed arithmetic behavior, which would evaluate to str[-1] if the string is empty.
  if (*str == str[(int)strlen(str) - 1])
    return "Equal";
  
  // unk_2004 is an undefined data reference in the .rdata or .data section,
  // likely pointing to a string such as "Not Equal".
  return (char *)&unk_2004;
}