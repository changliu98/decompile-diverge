void change_bit(int nr, void * addr)
{
 unsigned long * addr_local = (unsigned long *) addr;
 int nr_local = nr;

 addr_local[nr_local / 64] ^= 1UL << (nr_local % 64);
}