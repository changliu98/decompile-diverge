int func0(int n)
{
    int w;
    int isprime;
    int count = 0;
    unsigned __int64 current_num = 1; // Extracted from the upper 64 bits of the 128-bit integer

    while (count < n)
    {
        current_num++; // Equivalent to the 128-bit addition artifact

        isprime = 1;
        for (w = 2; w * w <= current_num; ++w)
        {
            if (current_num % w == 0)
            {
                isprime = 0;
                break;
            }
        }
        
        if (isprime)
            ++count;

        if (count == n)
            return current_num;
    }
    return 0;
}