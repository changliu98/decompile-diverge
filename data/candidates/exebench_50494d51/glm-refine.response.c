void set_bit(int nr, volatile unsigned long long *addr)
{
    addr[nr / 64] |= 1ULL << (nr % 64);
}