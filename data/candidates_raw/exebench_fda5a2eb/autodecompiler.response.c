void outw(unsigned short val, unsigned long port)
{
 *(volatile unsigned short *)port = val;
}