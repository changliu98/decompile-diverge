char *regex_test(char *text)
{
  int ret;
  struct regex_t re;
  if (regcomp(&re,"ab?",1))
    return "Not matched!";
  if (regexec(&re,text,0,((void *)0),0))
    return "Not matched!";
  return "Found a match!";
}