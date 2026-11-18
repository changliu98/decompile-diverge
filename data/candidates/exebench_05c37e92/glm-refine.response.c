void put_user_long(unsigned long long val, int *addr)
{
    *(unsigned long long *)addr = val;
}