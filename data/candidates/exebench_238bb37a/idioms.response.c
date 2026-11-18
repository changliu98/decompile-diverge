static long incr(long *var, long val)
{
    long old = *var;
    *var += val;
    return old;
}