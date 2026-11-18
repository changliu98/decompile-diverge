int rand_r(unsigned int *nextp)
{
 *nextp = *nextp * 1103515245 + 12345;
 return (unsigned int) (*nextp >> 16) & 0x7fff;
}