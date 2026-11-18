char *regex_test(char *text)
{
  char *re = "\\Bz\\B";
  int ret;
  char errbuf[100];
  struct regex_t re_comp;
  if (regcomp(&re_comp, re, 1))
  {
    fprintf(stderr, "Could not compile regex\n");
    return "Regex compilation error";
  }
  ret = regexec(&re_comp, text, 0, ((void *)0), 0);
  if (ret == 0)
  {
    return "Found a match!";
  }
  else if (ret == 1)
  {
    return "Not matched!";
  }
  else
  {
    regerror(ret, &re_comp, errbuf, sizeof(errbuf));
    fprintf(stderr, "Regex match failed: %s\n", errbuf);
    return "Regex execution error";
  }
}