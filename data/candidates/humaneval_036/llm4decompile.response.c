int func0(int n)
{
    int i, count = 0;
    for (i = 0; i < n; i++)
        if (i % 11 == 0 || i % 13 == 0)
            for (int q = i; q > 0; q /= 10)
                if (q % 10 == 7)
                    count++;
    return count;
}