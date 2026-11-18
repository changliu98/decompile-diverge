int factorf(int n, int f[])
{
    int k;
    f[0] = f[1] = f[2] = 0;
    if ((n%2 != 0) && (n%3 != 0) && (n%5 != 0))
    {
        k = 1;
    }
    else
    {
        if (n < 2)
        {
            k = 1;
        }
        else
        {
            while (1)
            {
                char c2 = (n%2 == 0) ? 0 : 1;
                if (c2 == 0)
                    break;
                f[0]++;
                n >>= 1;
            }
            while (1)
            {
                char c3 = (n%3 == 0) ? 0 : 1;
                if (c3 == 0)
                    break;
                f[1]++;
                n /= 3;
            }
            while (1)
            {
                char c5 = (n%5 == 0) ? 0 : 1;
                if (c5 == 0)
                    break;
                f[2]++;
                n /= 5;
            }
            if (n != 1)
            {
                k = 1;
            }
            else
            {
                k = 0;
            }
        }
    }
    return k;
}