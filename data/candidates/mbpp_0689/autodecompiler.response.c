int func0(int* coins, int size)
{
    int arr[size];
    if(size == 0 || !coins[0])
    {
        int i = 0;
        for(i = 0; i < size; i++)
            arr[i] = 0x7fffffff;
    }
    else
        arr[0] = 0;
    int i, j;
    for(i = 1; i < size; i++)
    {
        arr[i] = 0x7fffffff;
        for(j = 0; j < i; j++)
        {
            if(j+coins[j] >= i && arr[j] != 0x7fffffff)
                arr[i] = ((arr[j]+1)<(arr[i])?(arr[j]+1):(arr[i]));
        }
    }
    return arr[size-1];
}