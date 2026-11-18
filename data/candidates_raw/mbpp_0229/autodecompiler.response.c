int compare(int *a, int *b, int n)
{
    int i = 0;
    char result;

    while(1)
    {
        if(i >= n)
        {
            result = 1;
            break;
        }
        else if(a[i] == b[i])
        {
            i++;
        }
        else
        {
            result = 0;
            break;
        }
    }

    return result;
}