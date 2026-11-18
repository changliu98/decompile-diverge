const char *
func0(const char *str)
{
  regex_t re;
  int i;

  i = regcomp(&re, "a.*?b$", 0x01);
  if (i)
    {
      fprintf(*PTR_stderr_00103ff8, "Could not compile regex\n");
      return "Error";
    }

  i = regexec(&re, str, 0, NULL, 0);
  regfree(&re);
  if (!i)
    return "Found a match!";

  return "Not matched!";
}