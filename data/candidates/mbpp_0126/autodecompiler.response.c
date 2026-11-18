int func0(int a, int b)
{
    int i, j, k, p;
    p = 0;
    for(i = 1; ; i++)
    {
        if(i < a && i < b)
        {
            if(a % i == 0 && b % i == 0)
                p = p + i;
        }
        else
            return p;
    }
}