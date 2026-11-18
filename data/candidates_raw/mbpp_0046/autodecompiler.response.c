int check_row(int *array, int m)
{
    int i;
    int j;
    char ok;
    j = 0;
    while (j < m)
    {
        i = j + 1;
        while (i < m)
        {
            if (array[j] == array[i])
            {
                ok = 0;
                break ;
            }
            i++;
        }
        j++;
    }
    return (ok & 1);
}