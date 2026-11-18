int func0(char *listval[], int size)
{
    int i;
    int min_val = 2147483647;
    int current_val;
    for (i = 0; i < size; i++)
    {
        if (__isoc99_sscanf(listval[i], "%d", &current_val) && current_val < min_val)
            min_val = current_val;
    }
    return min_val;
}