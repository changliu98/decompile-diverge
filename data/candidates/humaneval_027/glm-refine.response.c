void __cdecl func0(const char *str, char *out)
{
  int length = strlen(str);

  for (int i = 0; i < length; ++i)
  {
    char c = str[i];
    
    if (std::islower(c))
    {
      c = std::toupper(c);
    }
    else if (std::isupper(c))
    {
      c = std::tolower(c);
    }
    
    out[i] = c;
  }
  
  out[length] = '\0';
}