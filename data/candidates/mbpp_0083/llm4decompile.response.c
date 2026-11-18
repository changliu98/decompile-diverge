char func0(char *strr)
{
    int i;
    int summ = 0;
    for (i = 0; strr[i] != 0; i++)
    {
        summ += strr[i] - 'a' + 1;
    }
    summ %= 26;
    if (summ == 0)
    {
        return 'z';
    }
    else
    {
        return summ + 'a' - 1;
    }
}