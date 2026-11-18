void word2string(uint value,char *buffer)

{
  int c;
  char *p;
  char *buffer_local;
  uint value_local;
  
  if (value == 0) {
    buffer[0] = '0';
    buffer[1] = ' ';
    buffer[2] = '\0';
    buffer[3] = '\0';
  }
  else {
    p = buffer;
    value_local = value;
    for (c = 0; c < 5; c = c + 1) {
      if (p + (ulong)value_local / (ulong)word2string::_smth[c] != buffer) {
        *p = (char)(value_local / word2string::_smth[c]) + '0';
        p = p + 1;
        value_local = value_local % word2string::_smth[c];
      }
    }
    p[0] = ' ';
    p[1] = '\0';
  }
  return;
}