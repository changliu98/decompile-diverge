static int hex2int(int c)
{
 int val;

 if ('a' <= c && c <= 'f')
  val = c + 10 - 'a';
 else if ('A' <= c && c <= 'F')
  val = c + 10 - 'A';
 else
  val = c - '0';

 return val;
}