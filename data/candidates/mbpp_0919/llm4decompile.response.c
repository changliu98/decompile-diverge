int func0(int *items, int length)
{
    int i;
    int tot = 1;

    for (i = 0; i < length; i++)
    {
        tot *= items[i];
    }

    return tot;
}