int func0(int *array, int size)
{
    int i, j;
    int max;
    for(i = 0; i < size; i++)
    {
        int count = 0;
        for(j = 0; j < size; j++)
        {
            if(array[i] == array[j])
                count++;
        }
        if(count % 2 != 0)
        {
            max = array[i];
            break;
        }
    }
    return max;
}