static int
and_peep2_q(int c, int *ec)
{
 *ec = c & 0xfe;
 return (c);
}