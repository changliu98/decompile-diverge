const char *__cdecl func0(const char *str)
{
  int has0 = 0;
  int has1 = 0;
  int has_other = 0;
  size_t len = strlen(str);

  for (size_t i = 0; i < len; ++i)
  {
    if (str[i] == '0')
    {
      has0 = 1;
    }
    else if (str[i] != '1')
    {
      has_other = 1;
      break;
    }
    else
    {
      has1 = 1;
    }
  }

  if ((has0 || has1) && !has_other)
    return "Yes"; // &unk_2004
  else
    return "No";  // &unk_2008
}