int check(int divisor, int non_divisor, int start, int end)
{
    int num = 0;
    int i = start;

    while(1)
    {
        if(i > end) break;
        if(i % divisor != 0) num++;
        if(num == non_divisor) return i;
        i++;
    }
    return i;
}