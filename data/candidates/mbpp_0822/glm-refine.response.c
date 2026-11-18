bool __cdecl func0(const char *p)
{
  int len = strlen(p);
  
  // Rule 1: Length must be between 6 and 12 inclusive
  if (len < 6 || len > 12)
    return false;

  bool hasLower = false;
  bool hasUpper = false;
  bool hasDigit = false;
  bool hasSpecial = false;

  for (int i = 0; i < len; ++i)
  {
    unsigned char c = p[i];
    
    // glibc __ctype_b_loc() bitmasks:
    // 0x200 = _ISlower
    // 0x100 = _ISupper
    // 0x800 = _ISdigit
    // 0x2000 = _ISspace
    if (islower(c))
    {
      hasLower = true;
    }
    else if (isupper(c))
    {
      hasUpper = true;
    }
    else if (isdigit(c))
    {
      hasDigit = true;
    }
    else if (c == '$' || c == '#' || c == '@')
    {
      hasSpecial = true;
    }
    else if (isspace(c))
    {
      // Rule 2: Spaces are strictly forbidden
      return false;
    }
  }

  // Rule 3: Must contain at least one lowercase, one uppercase, 
  // one digit, and one special character from {'$', '#', '@'}
  return hasLower && hasUpper && hasDigit && hasSpecial;
}