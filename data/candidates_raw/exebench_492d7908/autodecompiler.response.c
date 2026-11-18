void set_swap_short(short s, char *c)
{
 *(c+1) = (s >> 0) & 0xff;
 *(c) = (s >> 8) & 0xff;
}