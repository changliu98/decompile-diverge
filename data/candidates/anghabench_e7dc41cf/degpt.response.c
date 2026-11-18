bool issymbol(char c)

{
  char c_local;
  bool local_c;
  
  switch(c) {
  case ' ':
  case '%':
  case '(':
  case ')':
  case '*':
  case '+':
  case ',':
  case '-':
  case '<':
  case '>':
  case '[':
  case ']':
  case '{':
  case '}':
    local_c = 1;
    break;
  default:
    local_c = 0;
  }
  return local_c;
}