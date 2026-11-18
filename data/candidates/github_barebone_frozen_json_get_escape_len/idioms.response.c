int json_get_escape_len(char *str, int len)
{
  int ret;
  switch(*str)
  {
    case '"':
    case '\\':
    case 'n':
    case 'r':
    case 't':
    case 'b':
    case 'f':
    case '/':
      ret = (len < 2) ? -2 : 1;
      break;
    case 'u':
      if(len < 6)
      {
        ret = -2;
      }
      else
      {
        int is_hex = 0;
        is_hex = (is_hex && is_hexdigit(str[1])) ?
          is_hex && is_hexdigit(str[2]) :
          is_hex && is_hexdigit(str[3]) :
          is_hex && is_hexdigit(str[4]) :
          is_hex;
        ret = (is_hex) ? 5 : -1;
      }
      break;
    default:
      ret = -1;
      break;
  }
  return ret;
}