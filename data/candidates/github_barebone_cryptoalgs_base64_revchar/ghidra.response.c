BYTE revchar(char ch)

{
  char ch_local;
  
  if ((ch < 'A') || ('Z' < ch)) {
    if ((ch < 'a') || ('z' < ch)) {
      if ((ch < '0') || ('9' < ch)) {
        if (ch == '+') {
          ch_local = '>';
        }
        else {
          ch_local = ch;
          if (ch == '/') {
            ch_local = '?';
          }
        }
      }
      else {
        ch_local = ch + '\x04';
      }
    }
    else {
      ch_local = ch + -0x47;
    }
  }
  else {
    ch_local = ch + -0x41;
  }
  return ch_local;
}