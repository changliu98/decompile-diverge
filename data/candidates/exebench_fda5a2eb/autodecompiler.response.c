void put_user_word(unsigned short val, unsigned long port)
{
 *(volatile unsigned short *)port = val;
}