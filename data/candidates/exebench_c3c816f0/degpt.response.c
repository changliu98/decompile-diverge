int char2num(char c,char *pNum)

{
  int ret;
  char *pNum_local;
  char c_local;
  
  ret = 0;
  if ((c < '0') || ('9' < c)) {
    if ((c < 'A') || ('F' < c)) {
      if ((c < 'a') || ('f' < c)) {
        ret = -1;
      }
      else {
        *pNum = c + -0x57;
      }
    }
    else {
      *pNum = c + -0x37;
    }
  }
  else {
    *pNum = c + -0x30;
  }
  return ret;
}