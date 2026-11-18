BOOL __cdecl is_bool_str(char *str, BOOL *pbool)
{
  // Validate pointers
  if (!str || !pbool)
    return FALSE;

  // Check for true/affirmative strings
  if (!strcasecmp(str, "true") || !strcasecmp(str, "yes") || !strcasecmp(str, "on"))
  {
    *pbool = TRUE;
    return TRUE;
  }
  
  // Check for false/negative strings
  if (!strcasecmp(str, "false") || !strcasecmp(str, "no") || !strcasecmp(str, "off"))
  {
    *pbool = FALSE;
    return TRUE;
  }

  // Check for integer representations
  if (is_integer(str))
  {
    *pbool = (atoi64(str) != 0);
    return TRUE;
  }

  // Check for floating-point representations
  if (is_float(str))
  {
    *pbool = (atof(str) != 0.0);
    return TRUE;
  }

  // String format not recognized
  return FALSE;
}