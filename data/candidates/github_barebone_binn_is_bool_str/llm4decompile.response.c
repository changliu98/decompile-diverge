BOOL is_bool_str(const char *str, BOOL *pbool)
{
 if (!str || !pbool)
  return 0;

 if (!strcasecmp(str, "true") || !strcasecmp(str, "yes") || !strcasecmp(str, "on"))
  *pbool = 1;
 else if (!strcasecmp(str, "false") || !strcasecmp(str, "no") || !strcasecmp(str, "off"))
  *pbool = 0;
 else if (is_integer(str))
  *pbool = (atoi64(str) != 0);
 else if (is_float(str))
  *pbool = (atof(str) != 0.0);
 else
  return 0;

 return 1;
}