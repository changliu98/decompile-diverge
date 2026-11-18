int getDomainName(char *domain, int comboMax, int decode, char *result)
{
  int ret = 0;
  int pos;
  int comboxindex;
  char index[2];
  char *d = domain;
  char *r = result;
  strzero(r, 256);
  if (d[0]=='_') {
    pos = getPos(d+1, "__");
    if (pos > 0) {
      if (decode) {
        strzero(index, sizeof(index));
        copystr(index, d+(pos+1)+2, 1);
        comboxindex = getComboxIndex(index);
        if (comboxindex > 0 && comboxindex < comboMax)
          ret = comboxindex;
      }
      copystr(r, d+1, pos);
    }
    else
      copystr(r, d+1, 255);
  }
  return ret;
}