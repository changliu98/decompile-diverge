int foo(int *p)
{
    *p = 0xDEAD;
    return *p;
}