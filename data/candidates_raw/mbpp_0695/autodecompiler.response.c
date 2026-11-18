int _lexorder(int *t1, int *t2, int n)
{
    int i;
    char equal;
    for (i = 0; ; i++)
    {
        if (i >= n)
        {
            equal = 1;
            break;
        }
        if (t1[i] < t2[i])
            break;
        else if (t1[i] > t2[i])
        {
            equal = 0;
            break;
        }
    }
    return (equal & 1);
}