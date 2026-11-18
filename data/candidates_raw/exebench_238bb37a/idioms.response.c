static long get_and_add(long *var, long val)
{
    long old = *var;
    *var += val;
    return old;
}