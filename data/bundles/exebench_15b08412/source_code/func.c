
static int div_dbl(unsigned long u[2], unsigned long v)
{
    if ( (v == 0) || (u[1] >= v) )
        return 1;
    asm ( "div %4"
          : "=a" (u[0]), "=d" (u[1])
          : "0" (u[0]), "1" (u[1]), "r" (v) );
    return 0;
}
