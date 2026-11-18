void func0(int *my_list, int length)
{
    int gap, temp;
    int i, j;

    gap = length / 2;

    while (gap > 0)
    {
        for (i = gap; i < length; i++)
        {
            temp = my_list[i];
            j = i;

            while (j >= gap && my_list[j - gap] > temp)
            {
                my_list[j] = my_list[j - gap];
                j = j - gap;
            }

            my_list[j] = temp;
        }

        gap = gap / 2;
    }
}