int checkRow(int *array, int m)
{
    int i, j;
    char flag;
    for (i=0; i<m-1; i++)
    {
        for (j=i+1; j<m; j++)
        {
            if (array[i] == array[j])
            {
                flag = 0;
                break;
            }
        }
    }
    if (flag != 0) flag = 1;
    return flag;
}