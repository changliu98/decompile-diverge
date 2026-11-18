static int
e2b(int c, int *ec)
{
 *ec = c & 0xfe;
 return (c);
}