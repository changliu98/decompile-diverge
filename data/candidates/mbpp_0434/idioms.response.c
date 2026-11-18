char *func0(char *text)
{
  int ret;
  struct regex_t re;
  if (regcomp(&re,"ab+",1))
    return "Regex compilation failed!";
  ret = regexec(&re,text,0,((void *)0),0);
  regfree(&re);
  if (ret)
    return "Not matched!";
  else
    return "Found a match!";
}