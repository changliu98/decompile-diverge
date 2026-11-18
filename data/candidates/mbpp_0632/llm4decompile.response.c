void func0(int num_list[], int size, int result[])
{
    int i, j, zero_count = 0;
    for (i = 0, j = 0; i < size; i++)
    {
        if (num_list[i] == 0)
            zero_count++;
        else
            result[j++] = num_list[i];
    }
    for (i = 0; i < zero_count; i++)
        result[j++] = 0;
}