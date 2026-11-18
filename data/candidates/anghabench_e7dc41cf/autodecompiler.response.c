static int issymbol(char c)
{
 int ret;
 switch(c) {
  case '(': case ')': case '[': case ']':
  case '{': case '}': case '<': case '>':
  case '+': case '-': case '*': case '/':
  case '%': case '=': case '?': case ':':
  case ' ': ret = 1; break;
  default: ret = 0;
 }
 return ret;
}