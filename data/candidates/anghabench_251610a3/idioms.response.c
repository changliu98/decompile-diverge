char *get_level_str(int level)
{
  char *ret = "";
  switch (level) {
  case 128:
    ret = "warning";
    break;
  case 129:
    ret = "verbose";
    break;
  case 130:
    ret = "quiet";
    break;
  case 131:
    ret = "panic";
    break;
  case 132:
    ret = "info";
    break;
  case 133:
    ret = "fatal";
    break;
  case 134:
    ret = "error";
    break;
  case 135:
    ret = "debug";
    break;
  default:
    break;
  }
  return ret;
}