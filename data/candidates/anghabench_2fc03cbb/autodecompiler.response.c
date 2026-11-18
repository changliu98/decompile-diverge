static int a2d(char c)
{
 int val;

 if ('0' <= c && c <= '9')
  val = c - '0';
 else if ('a' <= c && c <= 'f')
  val = c - 'a' + 10;
 else if ('A' <= c && c <= 'F')
  val = c - 'A' + 10;
 else
  val = -1;

 return val;
}