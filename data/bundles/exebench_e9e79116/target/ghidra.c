void itoa(uint value,char *buffer)

{
  int c;
  char *buffer_local;
  uint value_local;
  
  c = 7;
  buffer[7] = '\0';
  value_local = value;
  do {
    buffer[c] = (char)(value_local % 10) + '0';
    value_local = value_local / 10;
    c = c + -1;
  } while (value_local != 0);
  return;
}