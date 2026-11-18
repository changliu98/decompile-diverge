int descape(struct charpair *in, struct charpair *out)
{
  int ret;
  if (in->first == '\\')
  {
    switch (in->second)
    {
      case '\"':
        out->second = '\"';
        ret = 1;
        break;
      case '\'':
        out->second = '\'';
        ret = 1;
        break;
      case '?':
        out->second = '?';
        ret = 1;
        break;
      case 'a':
        out->second = '\a';
        ret = 1;
        break;
      case 'b':
        out->second = '\b';
        ret = 1;
        break;
      case 'f':
        out->second = '\f';
        ret = 1;
        break;
      case 'n':
        out->second = '\n';
        ret = 1;
        break;
      case 'r':
        out->second = '\r';
        ret = 1;
        break;
      case 't':
        out->second = '\t';
        ret = 1;
        break;
      case 'v':
        out->second = '\v';
        ret = 1;
        break;
      default:
        break;
    }
  }
  else
  {
    out->first = in->first;
    out->second = in->second;
    ret = 0;
  }
  return ret;
}