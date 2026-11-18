int getPossibleCount(int *possibles, int *num)
{
    int count = 0;
    int i;
    for (i = 0; i < 9; i++)
    {
        if (possibles[i])
        {
            count++;
            if (num)
                *num = possibles[i];
        }
    }
    return count;
}