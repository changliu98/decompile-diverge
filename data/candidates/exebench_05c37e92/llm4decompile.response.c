extern inline void put_user_long(unsigned long val, unsigned long *addr)
{
 do { *(addr) = (val); } while (0);
}