char *
func0(char *str)
{
  regex_t regex;
  int ret;
  const char *pattern = "a.*?b$";
  char *buf;


  ret = regcomp(&regex, pattern, 0x01);
  if (ret) {
    buf = "Regex compilation failed.";
  } else {

    ret = regexec(&regex, str, 0, NULL, 0);
    if (!ret) {
      buf = "Found a match!";
    } else if (ret == 1) {
      buf = "Not matched!";
    } else {
      buf = "Regex match failed.";
    }
  }

  return buf;
}