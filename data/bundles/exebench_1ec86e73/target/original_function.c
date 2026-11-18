double frexp (double x, int* exp)
{
    int sign = 1;
    if(x < 0)
    {
        sign = -1;
        x *= sign;
    }
    else if(x == 0.0)
    {
        *exp = 0;
        return 0.0;
    }

    *exp = 0;
    int e = 1;
    double sig = x;
    while(sig < 0.5 || sig >= 1.0)
    {
        e *= 2;
        (*exp)++;
        sig = x/e;
    }
    return sig*sign;
}