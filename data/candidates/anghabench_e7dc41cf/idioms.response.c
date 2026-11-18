int issymbol(char c)
{
  int is_op = 0;
  switch(c)
  {
    case '+':
    case '-':
    case '*':
    case '/':
    case '<':
    case '>':
    case '%':
    case '(':
    case ')':
    case ',':
    case '[':
    case ']':
    case '{':
    case '}':
      is_op = 1;
      break;
    default:
      is_op = 0;
  }
  return is_op;
}