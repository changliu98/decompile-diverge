char read_escape_control_char(char c)

{
  char c_local;
  char local_9;
  
  if (c == 'n') {
    local_9 = '\n';
  }
  else if (c == 't') {
    local_9 = '\t';
  }
  else if (c == 'r') {
    local_9 = '\r';
  }
  else if (c == 'e') {
    local_9 = '\x1b';
  }
  else if (c == 'b') {
    local_9 = '\b';
  }
  else if (c == 'f') {
    local_9 = '\f';
  }
  else if (c == 'v') {
    local_9 = '\v';
  }
  else {
    local_9 = c;
    if (c == 'a') {
      local_9 = '\a';
    }
  }
  return local_9;
}