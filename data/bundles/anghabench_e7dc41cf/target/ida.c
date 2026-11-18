bool __cdecl issymbol(char c)
{
  bool v2; // [rsp+Ch] [rbp-4h]

  switch ( c )
  {
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
      v2 = 1;
      break;
    default:
      v2 = 0;
      break;
  }
  return v2;
}