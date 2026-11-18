int *func0(int arr[], int length, int output[])
{
    int i;
    int smallestEven = 2147483647;
    int index = -1;
    for (i = 0; i < length; i++)
    {
        if (arr[i] % 2 == 0)
        {
            if (arr[i] < smallestEven || index == -1)
            {
                smallestEven = arr[i];
                index = i;
            }
        }
    }
    if (index == -1)
    {
        return NULL;
    }
    output[0] = smallestEven;
    output[1] = index;
    return output;
}