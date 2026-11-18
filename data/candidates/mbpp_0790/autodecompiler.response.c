int func0(int *arr, int n)
{
    int i = 0;
    char flag;
    while(1)
    {
        if(i < n)
        {
            if(arr[i] % 2 != i % 2)
            {
                flag = 0;
                break;
            }
            else
            {
                i++;
            }
        }
        else
        {
            flag = 1;
            break;
        }
    }

    return flag & 1;
}